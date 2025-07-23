// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeGameplayState.h"

#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Services/HistoryService.h"

class UMyTestView;

void UInitializeGameplayState::Enter()
{
	auto HistoryService = StateMachine->InstallerContainer->Resolve<UHistoryService>();
	HistoryService->TryProgress();

	StateMachine->NextState();
}
