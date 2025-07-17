// Copyright Floruit, Inc. All Rights Reserved.


#include "MainMenuGameMode.h"

#include "VeilOfFaith/Installer/InstallerGameSubsystem.h"
#include "VeilOfFaith/Installer/StateMachine/InstallerStateMachine.h"
#include "VeilOfFaith/Installer/StateMachine/States/InitializeMainMenuState.h"
#include "VeilOfFaith/Installer/StateMachine/States/BeginWorldSystemsState.h"
#include "VeilOfFaith/Installer/StateMachine/States/TickSystemsState.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	StateMachine = GetGameInstance()->GetSubsystem<UInstallerGameSubsystem>()->StateMachine;
	
	StateMachine->Initialize({
		NewObject<UBeginWorldSystemsState>(World),
		NewObject<UInitializeMainMenuState>(World),

		NewObject<UTickSystemsState>(World)
	});
}
