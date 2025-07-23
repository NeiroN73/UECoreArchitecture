// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "UObject/Object.h"
#include "BeginWorldSystemsState.generated.h"

class IWorldable;
class UInstallerContainer;

UCLASS()
class PROJECTCORERUNTIME_API UBeginWorldSystemsState : public UInstallerState
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> Container;
	TArray<IWorldable*> Worldables;

	virtual void Enter() override;
};
