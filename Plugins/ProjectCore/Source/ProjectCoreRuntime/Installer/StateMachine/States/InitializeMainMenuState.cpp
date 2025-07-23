// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeMainMenuState.h"

#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Services/ScreensService.h"
#include "ProjectCoreRuntime/UI/MainMenu/MainMenuScreen.h"

void UInitializeMainMenuState::Enter()
{
	ViewsService = StateMachine->InstallerContainer->Resolve<UScreensService>();
	ViewsService->Open<UMainMenuScreen>();
	
	StateMachine->NextState();
}
