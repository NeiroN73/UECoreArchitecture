// Copyright Floruit, Inc. All Rights Reserved.


#include "BeginWorldSystemsState.h"

#include "VeilOfFaith/Factories/HandlersFactory.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Installer/StateMachine/InstallerStateMachine.h"

void UBeginWorldSystemsState::Enter()
{
	Container = StateMachine->InstallerContainer;
	
	Worldables = Container->ResolveAllImplements<IWorldable>();

	if (auto World = GetWorld())
	{
		for (auto Worldable : Worldables)
		{
			Worldable->WorldChanged(World);
		}
	}

	StateMachine->NextState();
}
