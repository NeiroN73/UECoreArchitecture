// Copyright Floruit, Inc. All Rights Reserved.


#include "InstallerGameMode.h"

#include "VeilOfFaith/Installer/StateMachine/InstallerStateMachine.h"

AInstallerGameMode::AInstallerGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInstallerGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (auto CurrentWorld = GetWorld())
	{
		World = CurrentWorld;
	}
}

void AInstallerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (StateMachine)
	{
		StateMachine->Tick(DeltaSeconds);
	}
}
