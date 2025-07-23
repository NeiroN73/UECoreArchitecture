// Copyright Floruit, Inc. All Rights Reserved.


#include "TickSystemsState.h"

#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Services/TickService.h"

void UTickSystemsState::Enter()
{
	TickService = StateMachine->InstallerContainer->Resolve<UTickService>();
}

void UTickSystemsState::Tick(float DeltaSeconds)
{
	TickService->Tick(DeltaSeconds);
}
