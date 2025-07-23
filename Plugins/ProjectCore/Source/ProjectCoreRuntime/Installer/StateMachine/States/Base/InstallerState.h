// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InstallerState.generated.h"

class UInstallerStateMachine;

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UInstallerState : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UInstallerStateMachine> StateMachine;

	UFUNCTION()
	virtual void Enter() {}

	UFUNCTION()
	virtual void Tick(float DeltaSeconds) {}
};
