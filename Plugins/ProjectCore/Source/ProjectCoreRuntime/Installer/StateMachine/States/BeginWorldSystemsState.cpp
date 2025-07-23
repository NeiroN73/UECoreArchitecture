// Copyright Floruit, Inc. All Rights Reserved.


#include "BeginWorldSystemsState.h"

#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"

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
