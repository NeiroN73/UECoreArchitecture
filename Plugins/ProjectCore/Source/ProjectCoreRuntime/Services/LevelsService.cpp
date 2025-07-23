// Copyright Floruit, Inc. All Rights Reserved.


#include "LevelsService.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectCoreRuntime/Configs/LevelsConfig.h"
#include "ProjectCoreRuntime/UI/Loading/LoadingScreen.h"

void ULevelsService::LoadLevelAsync(TSoftObjectPtr<UWorld> Level, FStreamableDelegate Callback)
{
	ViewsService->Open<ULoadingScreen>();
	AssetsService->LoadAsync(Level->GetFName(), Level.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, Level, Callback]
	{
		Callback.Execute();
		UGameplayStatics::OpenLevelBySoftObjectPtr(World, Level);
	}));
}

void ULevelsService::Inject(TObjectPtr<UInstallerContainer> Container)
{
	ViewsService = Container->Resolve<UScreensService>();
	LevelsConfig = Container->Resolve<ULevelsConfig>();
	AssetsService = Container->Resolve<UAssetsService>();
}

TObjectPtr<ULevelsConfig> ULevelsService::GetLevelsConfig()
{
	return LevelsConfig;
}
