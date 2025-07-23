// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InstallerGameMode.generated.h"

class UInstallerStateMachine;

UCLASS()
class PROJECTCORERUNTIME_API AInstallerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<UInstallerStateMachine> StateMachine;

	UPROPERTY()
	TObjectPtr<UWorld> World;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	AInstallerGameMode();
};
