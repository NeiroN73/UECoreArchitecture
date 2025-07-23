// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeGameplayState.h"

#include "ProjectCoreRuntime/Characters/PlayerHandler.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Services/HistoryService.h"
#include "ProjectCoreRuntime/Services/ScreensService.h"

class UMyTestView;

void UInitializeGameplayState::Enter()
{
	auto HandlerFactory = StateMachine->InstallerContainer->Resolve<UHandlersFactory>();
	HandlerFactory->SpawnCharacterHandler<APlayerHandler>("player_handler", FVector::ZeroVector,
		FRotator::ZeroRotator);
	
	// auto ViewsService = StateMachine->InstallerContainer->Resolve<UScreensService>();
	// ViewsService->Open<UMyTestView>();

	auto HistoryService = StateMachine->InstallerContainer->Resolve<UHistoryService>();
	HistoryService->TryProgress();

	StateMachine->NextState();
}
