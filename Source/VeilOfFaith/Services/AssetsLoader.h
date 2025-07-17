// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "UObject/Object.h"
#include "VeilOfFaith/Services/Base/Service.h"
#include "AssetsLoader.generated.h"

struct FStreamableHandle;

UCLASS()
class VEILOFFAITH_API UAssetsService : public UService
{
	GENERATED_BODY()

public:
	void LoadAsync(FName Id, const FSoftObjectPath& TargetToStream, FStreamableDelegate Delegate);
	TSharedPtr<FStreamableHandle> LoadPrimaryAsync(const FPrimaryAssetId& AssetToLoad, FStreamableDelegate Delegate);

	TMap<FName, TSharedPtr<FStreamableHandle>> HandlesById;
	
	template<typename TObject = UObject>
	TObject* GetLoadedAsset(FName Id)
	{
		if (auto Asset = HandlesById.FindRef(Id))
		{
			if (Asset && Asset->HasLoadCompleted())
			{
				return Cast<TObject>(Asset->GetLoadedAsset());
			}
		}
		return nullptr;
	}
};
