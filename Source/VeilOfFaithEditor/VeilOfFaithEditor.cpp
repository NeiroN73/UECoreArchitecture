// Copyright Epic Games, Inc. All Rights Reserved.

#include "VeilOfFaithEditor.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "CustomId/CustomIdPropertyTypeCustomization.h"
#include "Modules/ModuleManager.h"
#include "Toolkits/ToolkitManager.h"
#include "VeilOfFaith/History/Elements/HistoryElement.h"

IMPLEMENT_MODULE(FVeilOfFaithEditor, VeilOfFaithEditor)

void FVeilOfFaithEditor::StartupModule()
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

void FVeilOfFaithEditor::ShutdownModule()
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