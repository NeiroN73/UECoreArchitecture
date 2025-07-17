// Copyright Floruit, Inc. All Rights Reserved.


#include "EntryPointGameMode.h"

#include "VeilOfFaith/Installer/InstallerGameSubsystem.h"
#include "VeilOfFaith/Installer/StateMachine/InstallerStateMachine.h"
#include "VeilOfFaith/Installer/StateMachine/States/BeginWorldSystemsState.h"
#include "VeilOfFaith/Installer/StateMachine/States/GoToMainMenuState.h"
#include "VeilOfFaith/Installer/StateMachine/States/LoadConfigsState.h"
#include "VeilOfFaith/Installer/StateMachine/States/InitializeSystemsState.h"

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
