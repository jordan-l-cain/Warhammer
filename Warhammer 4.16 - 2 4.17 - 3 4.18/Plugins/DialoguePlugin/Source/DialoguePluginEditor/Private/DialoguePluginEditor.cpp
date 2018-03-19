#include "DialoguePluginEditorPrivatePCH.h"
#include "IDialoguePluginEditorModule.h"
#include "DialoguePluginEditorSettingsDetails.h"
#include "DialogueAssetTypeActions.h"
#include "DialogueEditorStyle.h"
#include "Runtime/Core/Public/Features/IModularFeatures.h"
#include "Runtime/SlateCore/Public/Rendering/SlateRenderer.h"
#include "Editor/MainFrame/Public/Interfaces/IMainFrameModule.h"
#include "ISettingsModule.h"
#include "LevelEditor.h"
#include "ModuleManager.h"

#define LOCTEXT_NAMESPACE "DialoguePluginEditor"

class FDialoguePluginEditorModule : public IDialoguePluginEditorModule
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** IDialoguePluginEditorModule implementation */
	virtual bool AllowAutomaticGraphicsSwitching() override;
	virtual bool AllowMultipleGPUs() override;
	
private:
	void Initialize( TSharedPtr<SWindow> InRootWindow, bool bIsNewProjectWindow );
	void AddGraphicsSwitcher( FToolBarBuilder& ToolBarBuilder );
	
private:
	TSharedPtr< FExtender > NotificationBarExtender;
	bool bAllowAutomaticGraphicsSwitching;
	bool bAllowMultiGPUs;

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
	{
		AssetTools.RegisterAssetTypeActions(Action);		
	}
};

IMPLEMENT_MODULE(FDialoguePluginEditorModule, DialoguePluginEditor)

void FDialoguePluginEditorModule::StartupModule()
{	
	FDialogueEditorStyle::Initialize(); 

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("Dialogue", FOnGetDetailCustomizationInstance::CreateStatic(&FDialoguePluginEditorSettingsDetails::MakeInstance));

	PropertyModule.NotifyCustomizationModuleChanged();

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	EAssetTypeCategories::Type AssetCategoryBit = EAssetTypeCategories::Misc;

	TSharedRef<IAssetTypeActions> Action = MakeShareable(new FDialogueAssetTypeActions(AssetCategoryBit));

	RegisterAssetTypeAction(AssetTools, Action);
}

void FDialoguePluginEditorModule::Initialize( TSharedPtr<SWindow> InRootWindow, bool bIsNewProjectWindow )
{

}

void FDialoguePluginEditorModule::AddGraphicsSwitcher( FToolBarBuilder& ToolBarBuilder )
{
	
}

void FDialoguePluginEditorModule::ShutdownModule()
{
	FDialogueEditorStyle::Shutdown();
}

bool FDialoguePluginEditorModule::AllowAutomaticGraphicsSwitching()
{
	return bAllowAutomaticGraphicsSwitching;
}

bool FDialoguePluginEditorModule::AllowMultipleGPUs()
{
	return bAllowMultiGPUs;
}



#undef LOCTEXT_NAMESPACE
