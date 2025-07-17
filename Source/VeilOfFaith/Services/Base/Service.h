// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VeilOfFaith/Installer/Worldable.h"
#include "VeilOfFaith/SaveStates/Base/SaveState.h"
#include "Service.generated.h"

class UInstallerContainer;
class USaveState;

UCLASS(Abstract)
class VEILOFFAITH_API UService : public UObject,
public IWorldable
{
	GENERATED_BODY()

protected:
	template<typename TSaveState = USaveState>
	TSaveState* CreateSaveState()
	{
		USaveState* State = NewObject<TSaveState>();
		return Cast<TSaveState>(State);
	}

public:
	virtual void WorldChanged(UWorld* NewWorld) override;

	UPROPERTY()
	TObjectPtr<UWorld> World;
};
