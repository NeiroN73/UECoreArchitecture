// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Configs.generated.h"

class UConfig;

UCLASS()
class VEILOFFAITH_API UConfigs : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<UConfig*> Configs;

	UPROPERTY(EditAnywhere)
	TArray<UDataTable*> TableConfigs;
};