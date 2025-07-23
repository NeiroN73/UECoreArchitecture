// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ProjectCoreRuntime/SaveData/HistorySaveData.h"
#include "DataSaveGame.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UDataSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FHistorySaveData HistorySaveData;
};
