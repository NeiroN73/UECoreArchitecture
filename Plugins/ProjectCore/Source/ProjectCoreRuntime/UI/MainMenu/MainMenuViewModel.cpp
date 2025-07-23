// Copyright Floruit, Inc. All Rights Reserved.


#include "MainMenuViewModel.h"


void UMainMenuViewModel::Inject(TObjectPtr<UInstallerContainer> Container)
{
	LevelsService = Container->Resolve<ULevelsService>();
}

void UMainMenuViewModel::Bind()
{
	// BindContinueButton([this]
	// {
	// 	LevelsService->LoadLevelAsync(LevelsService->GetLevelsConfig()->GameplayLevel,
	// 		FStreamableDelegate::CreateLambda([this]
	// 	{
	// 			
	// 	}));
	// });
}
