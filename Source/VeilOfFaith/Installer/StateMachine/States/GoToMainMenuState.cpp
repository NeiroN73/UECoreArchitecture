// Copyright Floruit, Inc. All Rights Reserved.


#include "GoToMainMenuState.h"

#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Installer/StateMachine/InstallerStateMachine.h"
#include "VeilOfFaith/Services/LevelsService.h"

void UGoToMainMenuState::Enter()
{
	LevelsService = StateMachine->InstallerContainer->Resolve<ULevelsService>();
	LevelsService->LoadLevelAsync(LevelsService->GetLevelsConfig()->MainMenuLevel,
		FStreamableDelegate::CreateLambda([this]
	{
		StateMachine->NextState();
	}));
}
