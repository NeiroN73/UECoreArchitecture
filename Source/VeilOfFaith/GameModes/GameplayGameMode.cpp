// Copyright Floruit, Inc. All Rights Reserved.


#include "GameplayGameMode.h"

#include "VeilOfFaith/Installer/InstallerGameSubsystem.h"
#include "VeilOfFaith/Installer/StateMachine/States/BeginWorldSystemsState.h"
#include "VeilOfFaith/Installer/StateMachine/States/InitializeGameplayState.h"
#include "VeilOfFaith/Installer/StateMachine/States/InitializeSystemsState.h"
#include "VeilOfFaith/Installer/StateMachine/States/LoadConfigsState.h"
#include "VeilOfFaith/Installer/StateMachine/States/TickSystemsState.h"

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