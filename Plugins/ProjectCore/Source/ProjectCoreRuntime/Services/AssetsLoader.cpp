// Copyright Floruit, Inc. All Rights Reserved.


#include "AssetsLoader.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UAssetsService::LoadAsync(FName Id, const FSoftObjectPath& TargetToStream,
	FStreamableDelegate Delegate)
{
	if (UAssetManager::IsInitialized())
	{
		auto Handle = UAssetManager::GetStreamableManager().RequestAsyncLoad(TargetToStream, Delegate);
		HandlesById.Add(Id, Handle);
	}
}

TSharedPtr<FStreamableHandle> UAssetsService::LoadPrimaryAsync(const FPrimaryAssetId& AssetToLoad,
	FStreamableDelegate Delegate)
{
	if (auto AssetManager = UAssetManager::GetIfInitialized())
	{
		return AssetManager->LoadPrimaryAsset(AssetToLoad, TArray<FName>(), Delegate);
	}
	
	return TSharedPtr<FStreamableHandle>();
}
