// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeMainMenuState.h"

#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Installer/StateMachine/InstallerStateMachine.h"
#include "VeilOfFaith/Services/ScreensService.h"
#include "VeilOfFaith/UI/MainMenu/MainMenuScreen.h"

void UInitializeMainMenuState::Enter()
{
	ViewsService = StateMachine->InstallerContainer->Resolve<UScreensService>();
	ViewsService->Open<UMainMenuScreen>();
	
	StateMachine->NextState();
}
