// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/SaveData.h"
#include "HistorySaveData.generated.h"

USTRUCT()
struct VEILOFFAITH_API FHistorySaveData : public FSaveData
{
	GENERATED_BODY()

	TArray<FGuid> CurrentElementIds;
};
