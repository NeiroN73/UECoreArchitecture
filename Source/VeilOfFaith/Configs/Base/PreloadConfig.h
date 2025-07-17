// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VeilOfFaith/EditorUtils/CustomId.h"
#include "PreloadConfig.generated.h"

class UPreloadsService;

UINTERFACE()
class UPreloadConfig : public UInterface
{
	GENERATED_BODY()
};

class VEILOFFAITH_API IPreloadConfig
{
	GENERATED_BODY()

public:
	virtual TMap<FName, FSoftObjectPath> GetSoftPaths() = 0;
	//virtual void SetLoadedAssets(TMap<FName, UObject*> Assets) = 0;

	template<class TPreload = UObject>
	TMap<FName, FSoftObjectPath> ToSoftPaths(TMap<FCustomId, TSoftObjectPtr<TPreload>> InPreloadByIds)
	{
		TMap<FName, FSoftObjectPath> Map;
		for (auto Element : InPreloadByIds)
		{
			Map.Add(Element.Key, Element.Value.ToSoftObjectPath());
		}
		return Map;
	}
	
	template<class TPreload = UObject>
	TMap<FName, TObjectPtr<TPreload>> CastMap(TMap<FName, UObject*> Assets)
	{
		TMap<FName, TObjectPtr<TPreload>> ResultMap;
		for (auto& Element : Assets)
		{
			if (TPreload* Casted = Cast<TPreload>(Element.Value))
			{
				ResultMap.Add(Element.Key, TObjectPtr<TPreload>(Casted));
			}
		}
		return ResultMap;
	}
};
