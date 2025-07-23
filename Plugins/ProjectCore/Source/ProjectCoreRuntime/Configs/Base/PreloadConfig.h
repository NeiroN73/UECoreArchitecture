// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "UObject/Interface.h"
#include "PreloadConfig.generated.h"

UINTERFACE()
class UPreloadConfig : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IPreloadConfig
{
	GENERATED_BODY()

public:
	virtual TMap<FName, FSoftObjectPath> GetSoftPaths() = 0;

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
};
