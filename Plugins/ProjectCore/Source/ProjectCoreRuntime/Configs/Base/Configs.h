// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Configs.generated.h"

class UConfig;

UCLASS()
class PROJECTCORERUNTIME_API UConfigs : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UConfig>> Configs;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UDataTable>> TableConfigs;
};