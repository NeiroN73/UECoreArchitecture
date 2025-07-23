// Copyright Floruit, Inc. All Rights Reserved.


#include "MainMenuGameMode.h"

#include "ProjectCoreRuntime/Installer/InstallerGameSubsystem.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/BeginWorldSystemsState.h"
#include "ProjectCoreRuntime/Installer/StateMachine/States/TickSystemsState.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	StateMachine = GetGameInstance()->GetSubsystem<UInstallerGameSubsystem>()->StateMachine;
	
	StateMachine->Initialize({
		NewObject<UBeginWorldSystemsState>(World),

		NewObject<UTickSystemsState>(World)
	});
}
