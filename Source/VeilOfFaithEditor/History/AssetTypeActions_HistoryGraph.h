// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class VEILOFFAITHEDITOR_API FAssetTypeActions_HistoryGraph : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_HistoryGraph(EAssetTypeCategories::Type InAssetCategory) : AssetCategory(InAssetCategory) {}

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects,
		TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	uint32 GetCategories() override
	{
		return AssetCategory;
	}
	
protected:
	EAssetTypeCategories::Type AssetCategory;
};
