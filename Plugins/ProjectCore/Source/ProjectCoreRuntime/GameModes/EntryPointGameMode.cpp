// Copyright Floruit, Inc. All Rights Reserved.


#include "EntryPointGameMode.h"

#include "ProjectCoreRuntime/Installer/InstallerGameSubsystem.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/BeginWorldSystemsState.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/GoToMainMenuState.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/LoadConfigsState.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/InitializeSystemsState.h"

void AEntryPointGameMode::BeginPlay()
{
	Super::BeginPlay();

	StateMachine = NewObject<UInstallerStateMachine>();
	GetGameInstance()->GetSubsystem<UInstallerGameSubsystem>()->StateMachine = StateMachine;
	
	StateMachine->Initialize({
		NewObject<ULoadConfigsState>(),
		NewObject<UInitializeSystemsState>(),
		
		NewObject<UBeginWorldSystemsState>(World),
		NewObject<UGoToMainMenuState>(World)
	});
}
