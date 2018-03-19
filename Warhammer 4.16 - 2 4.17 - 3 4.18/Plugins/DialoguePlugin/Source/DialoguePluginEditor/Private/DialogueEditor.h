#pragma once

#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/AssetEditorManager.h"
#include "Editor/EditorWidgets/Public/ITransportControl.h"
#include "Dialogue.h"

class SDialogueViewportWidget;

class FDialogueEditor : public FAssetEditorToolkit, public FEditorUndoClient, FGCObject
{
public:
	FDialogueEditor();
	virtual ~FDialogueEditor();

	// IToolkit interface
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	// End of IToolkit interface

	//~ Begin FEditorUndoClient Interface
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;
	// End of FEditorUndoClient

	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;				// Must implement in derived class!
	virtual FText GetBaseToolkitName() const override;			// Must implement in derived class!
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;

	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	//virtual FString GetDocumentationLink() const override;
	virtual bool IsAssetEditor() const override;
	//virtual const TArray< UObject* >* GetObjectsCurrentlyBeingEdited() const override;
	virtual class FEdMode* GetEditorMode() const override;
	// End of FAssetEditorToolkit

	// FSerializableObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End of FSerializableObject interface

	TSharedPtr<SDialogueViewportWidget> DialogueViewportWidget;

public:
	void InitDialogueEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UDialogue* InitDialogue);
	UDialogue* GetDialogueBeingEdited() const { return DialogueBeingEdited; }

	bool refreshDetails;
	
protected:
	/** The object we're currently editing */
	UDialogue* DialogueBeingEdited;
	/** The object we're currently editing */
	//TArray<UObject*> EditingObjects;

protected:

	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);
};
