// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/SaveData/Base/DataSaveGame.h"
#include "SaveState.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API USaveState : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UDataSaveGame* SaveGame;
	UPROPERTY()
	bool bSaveDataInitialized;

	virtual void Read() PURE_VIRTUAL(USaveState::Read())
	virtual void Write() PURE_VIRTUAL(USaveState::Write())
};