// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeCategories.h"
#include "History/AssetTypeActions_HistoryGraph.h"
#include "History/HistoryGraphEditor.h"

class UHistoryGraph;
class IAssetTypeActions;

class VEILOFFAITHEDITOR_API FVeilOfFaithEditor : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;

private:
	EAssetTypeCategories::Type DlgSystemAssetCategoryBit;

	TArray<TSharedPtr<IAssetTypeActions>> RegisteredAssetTypeActions;

	template<typename T = FAssetTypeActions_HistoryGraph>
	void CreateAssetTypeActions(IAssetTools& AssetTools)
	{
		auto Action = MakeShared<T>(DlgSystemAssetCategoryBit);
		AssetTools.RegisterAssetTypeActions(Action);
		RegisteredAssetTypeActions.Add(Action);
	}
};
