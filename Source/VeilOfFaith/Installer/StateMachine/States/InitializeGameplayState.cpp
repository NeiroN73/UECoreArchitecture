// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeGameplayState.h"

#include "VeilOfFaith/Characters/PlayerHandler.h"
#include "VeilOfFaith/Factories/HandlersFactory.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Installer/StateMachine/InstallerStateMachine.h"
#include "VeilOfFaith/Services/HistoryService.h"
#include "VeilOfFaith/Services/ScreensService.h"

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
