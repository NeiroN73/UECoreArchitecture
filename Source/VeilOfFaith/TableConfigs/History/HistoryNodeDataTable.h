// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Conditions.h"
#include "HistoryNodeDataTable.generated.h"

USTRUCT(BlueprintType)
struct VEILOFFAITH_API FHistoryNodeDataTable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EConditions Condition = EConditions::And;
};
