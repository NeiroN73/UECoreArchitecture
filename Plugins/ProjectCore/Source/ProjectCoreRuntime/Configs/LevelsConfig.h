// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "UObject/Object.h"
#include "LevelsConfig.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API ULevelsConfig : public UConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> EntryPointLevel;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenuLevel;
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> GameplayLevel;
};
