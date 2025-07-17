// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "IdsConfig.generated.h"

UCLASS()
class VEILOFFAITHEDITOR_API UIdsConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FName> Ids;
};
