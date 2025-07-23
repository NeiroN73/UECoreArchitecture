#include "ProjectCoreEditor.h"

#include "CustomId/CustomIdPropertyTypeCustomization.h"

#define LOCTEXT_NAMESPACE "FProjectCoreEditorModule"

void FProjectCoreEditorModule::StartupModule()
{
	IModuleInterface::StartupModule();

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();
	
	DlgSystemAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory("History System",
		NSLOCTEXT("HistorySystemEditor", "HistorySystemAssetCategory", "History System"));
	{
		CreateAssetTypeActions<FAssetTypeActions_HistoryGraph>(AssetTools);
	}

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	PropertyModule.RegisterCustomPropertyTypeLayout(
		"CustomId",
		FOnGetPropertyTypeCustomizationInstance::
		CreateStatic(&FCustomIdPropertyTypeCustomization::MakeInstance)
	);

	// PropertyModule.RegisterCustomClassLayout(
	// 	UHistoryGraphNode::StaticClass()->GetFName(),
	// 	FOnGetDetailCustomizationInstance::CreateStatic(&FHistoryDetailsCustomization::MakeInstance)
	// );

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FProjectCoreEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (auto TypeAction : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(TypeAction.ToSharedRef());
		}
	}
	RegisteredAssetTypeActions.Empty();

	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomPropertyTypeLayout("CustomId");
	}
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FProjectCoreEditorModule, ProjectCoreEditor)