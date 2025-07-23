// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Conditions.h"
#include "HistoryNodeDataTable.generated.h"

USTRUCT(BlueprintType)
struct PROJECTCORERUNTIME_API FHistoryNodeDataTable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EConditions Condition = EConditions::And;
};
