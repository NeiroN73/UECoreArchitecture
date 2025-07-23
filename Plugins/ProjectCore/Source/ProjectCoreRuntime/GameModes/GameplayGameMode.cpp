// Copyright Floruit, Inc. All Rights Reserved.


#include "GameplayGameMode.h"

#include "ProjectCoreRuntime/Installer/InstallerGameSubsystem.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/BeginWorldSystemsState.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/InitializeGameplayState.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/InitializeSystemsState.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/LoadConfigsState.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/TickSystemsState.h"

void AGameplayGameMode::BeginPlay()
{
	Super::BeginPlay();

	StateMachine = NewObject<UInstallerStateMachine>();//debug
	GetGameInstance()->GetSubsystem<UInstallerGameSubsystem>()->StateMachine = StateMachine;//debug
	
	StateMachine->Initialize({
		NewObject<ULoadConfigsState>(),//debug
		NewObject<UInitializeSystemsState>(),//debug
		
		NewObject<UBeginWorldSystemsState>(World),
		NewObject<UInitializeGameplayState>(World),

		NewObject<UTickSystemsState>(World)
	});
}