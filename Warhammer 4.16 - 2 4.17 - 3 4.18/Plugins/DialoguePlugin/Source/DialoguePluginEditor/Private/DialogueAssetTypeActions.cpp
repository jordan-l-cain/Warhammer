#include "DialogueAssetTypeActions.h"
#include "DialoguePluginEditorPrivatePCH.h"
#include "DialogueEditor.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"


FDialogueAssetTypeActions::FDialogueAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FDialogueAssetTypeActions::GetName() const
{
	return LOCTEXT("FDialogueAssetTypeActionsName", "Dialogue");
}

FColor FDialogueAssetTypeActions::GetTypeColor() const
{
	return FColor(129, 196, 115);
}

UClass* FDialogueAssetTypeActions::GetSupportedClass() const
{
	return UDialogue::StaticClass();
}

void FDialogueAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UDialogue* Dialogue = Cast<UDialogue>(*ObjIt))
		{
			TSharedRef<FDialogueEditor> NewDialogueEditor(new FDialogueEditor());
			NewDialogueEditor->InitDialogueEditor(Mode, EditWithinLevelEditor, Dialogue);
		}
	}
}

uint32 FDialogueAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc; //only affects filters
}

#undef LOCTEXT_NAMESPACE
