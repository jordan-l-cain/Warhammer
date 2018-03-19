#include "DialoguePluginEditorSettingsDetails.h"
#include "DialoguePluginEditorPrivatePCH.h"
#include "Dialogue.h"
#include "DialogueViewportWidget.h"
#include "Editor/UnrealEd/Public/ScopedTransaction.h"


#define LOCTEXT_NAMESPACE "DialoguePluginSettingsDetails"

TSharedRef<IDetailCustomization> FDialoguePluginEditorSettingsDetails::MakeInstance()
{
	return MakeShareable(new FDialoguePluginEditorSettingsDetails());
}

void FDialoguePluginEditorSettingsDetails::CustomizeDetails( IDetailLayoutBuilder& DetailLayout )
{
	DetailLayoutBuilder = &DetailLayout;

	const TSharedPtr<IPropertyHandle> DataProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogue, Data));
	DetailLayout.HideProperty(DataProperty);
	const TSharedPtr<IPropertyHandle> NextNodeProperty = DetailLayout.GetProperty(GET_MEMBER_NAME_CHECKED(UDialogue, NextNodeId));
	DetailLayout.HideProperty(NextNodeProperty);

	// Create a category so this is displayed early in the properties
	IDetailCategoryBuilder& MyCategory = DetailLayout.EditCategory("Dialogue Editor");
	IDetailCategoryBuilder& CurrentNodeCategory = DetailLayout.EditCategory("Current Node", LOCTEXT("CurrentNode", "Current Node"), ECategoryPriority::Important);

	TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;

	DetailLayout.GetObjectsBeingCustomized(ObjectsBeingCustomized);
	TArray<UObject*> StrongObjects;
	CopyFromWeakArray(StrongObjects, ObjectsBeingCustomized);

	if (StrongObjects.Num() == 0) return;

	UDialogue* Dialogue = Cast<UDialogue>(StrongObjects[0]);
	
	if (Dialogue->CurrentNodeId != -1 && Dialogue->CurrentNodeId != 0) //display current node details:
	{
		int32 index;
		FDialogueNode CurrentNode = Dialogue->GetNodeById(Dialogue->CurrentNodeId, index);

		CurrentNodeCategory.AddCustomRow(LOCTEXT("Text", "Text")).NameContent()
			[
				SNew(STextBlock).Font(IDetailLayoutBuilder::GetDetailFont())
				.Text(LOCTEXT("Text", "Text"))
			];

		CurrentNodeCategory.AddCustomRow(LOCTEXT("TextValue", "TextValue"))
			[
				SNew(SBox)
				.HeightOverride(100)
				[
					SNew(SMultiLineEditableTextBox).Text(CurrentNode.Text)
					.AutoWrapText(true)
					.OnTextCommitted(this, &FDialoguePluginEditorSettingsDetails::TextCommited, Dialogue, Dialogue->CurrentNodeId)
					.ModiferKeyForNewLine(EModifierKey::Shift)
				]
				
			];
			
		const TSharedPtr<IPropertyHandleArray> Array = DataProperty->AsArray();
		const TSharedPtr<IPropertyHandle> Child = Array->GetElement(index);
		const TSharedPtr<IPropertyHandle> IsPlayerField = Child->GetChildHandle("isPlayer");
		const TSharedPtr<IPropertyHandle> EventsField = Child->GetChildHandle("Events");
		const TSharedPtr<IPropertyHandle> ConditionsField = Child->GetChildHandle("Conditions");
		const TSharedPtr<IPropertyHandle> SoundField = Child->GetChildHandle("Sound");
		const TSharedPtr<IPropertyHandle> DialogueWaveField = Child->GetChildHandle("DialogueWave");
		const TSharedPtr<IPropertyHandle> HasEventsField = Child->GetChildHandle("bHasEvents");
		const TSharedPtr<IPropertyHandle> HasConditionsField = Child->GetChildHandle("bHasConditions");
		
		CurrentNodeCategory.AddProperty(IsPlayerField);
		CurrentNodeCategory.AddProperty(HasEventsField);
		CurrentNodeCategory.AddProperty(HasConditionsField);
		CurrentNodeCategory.AddProperty(EventsField);
		CurrentNodeCategory.AddProperty(ConditionsField);
		CurrentNodeCategory.AddProperty(SoundField);
		CurrentNodeCategory.AddProperty(DialogueWaveField);
	}	
	
}

void FDialoguePluginEditorSettingsDetails::TextCommited(const FText& NewText, ETextCommit::Type CommitInfo, UDialogue* Dialogue, int32 id)
{
	int32 index;
	FDialogueNode CurrentNode = Dialogue->GetNodeById(id, index);

	// we don't commit text if it hasn't changed
	if (Dialogue->Data[index].Text.EqualTo(NewText))
	{
		return;
	}
	
	const FScopedTransaction Transaction(LOCTEXT("TextCommited", "Edited Node Text"));
	Dialogue->Modify();
	
	Dialogue->Data[index].Text = NewText;
}

#undef LOCTEXT_NAMESPACE
