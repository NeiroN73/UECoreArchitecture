// Copyright Floruit, Inc. All Rights Reserved.


#include "AssetTypeActions_HistoryGraph.h"

#include "VeilOfFaith/History/Elements/RootHistoryElement.h"
#include "VeilOfFaith/History/Elements/HistoryElement.h"
#include "VeilOfFaithEditor/History/HistoryGraphEditor.h"

FText FAssetTypeActions_HistoryGraph::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_CustomGraph", "History");
}

FColor FAssetTypeActions_HistoryGraph::GetTypeColor() const
{
	return FColor(120, 0, 120);
}

UClass* FAssetTypeActions_HistoryGraph::GetSupportedClass() const
{
	return URootHistoryElement::StaticClass();
}

void FAssetTypeActions_HistoryGraph::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	for (UObject* Object : InObjects)
	{
		if (URootHistoryElement* History = Cast<URootHistoryElement>(Object))
		{
			TSharedRef<FHistoryGraphEditor> NewHistoryEditor(new FHistoryGraphEditor());
			NewHistoryEditor->InitHistoryGraphAssetEditor(EToolkitMode::Standalone, EditWithinLevelEditor, History, History);
		}
	}
}