// Copyright Floruit, Inc. All Rights Reserved.


#include "TickSystemsState.h"

#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Installer/StateMachine/InstallerStateMachine.h"
#include "VeilOfFaith/Services/TickService.h"

void UTickSystemsState::Enter()
{
	TickService = StateMachine->InstallerContainer->Resolve<UTickService>();
}

void UTickSystemsState::Tick(float DeltaSeconds)
{
	TickService->Tick(DeltaSeconds);
}
