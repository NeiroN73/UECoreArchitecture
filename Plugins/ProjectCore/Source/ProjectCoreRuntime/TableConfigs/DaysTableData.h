// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/TableData.h"
#include "DaysTableData.generated.h"

USTRUCT()
struct PROJECTCORERUNTIME_API FDaysTableData : public FTableData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	int32 Value;
};