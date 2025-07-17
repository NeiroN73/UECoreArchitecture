// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VeilOfFaith/SaveData/HistorySaveData.h"
#include "DataSaveGame.generated.h"

UCLASS()
class VEILOFFAITH_API UDataSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FHistorySaveData HistorySaveData;
};
