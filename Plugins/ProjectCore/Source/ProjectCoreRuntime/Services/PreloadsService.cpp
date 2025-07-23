// Copyright Floruit, Inc. All Rights Reserved.


#include "PreloadsService.h"

#include "AssetsLoader.h"
#include "ScreensService.h"
#include "ProjectCoreRuntime/Configs/Base/PreloadConfig.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/UI/Loading/LoadingScreen.h"

void UPreloadsService::Inject(TObjectPtr<UInstallerContainer> Container)
{
	PreloadConfigs = Container->ResolveAllImplements<IPreloadConfig>();
	
	AssetsService = Container->Resolve<UAssetsService>();
	ScreensService = Container->Resolve<UScreensService>();
}

void UPreloadsService::Initialize()
{
	//HistoryService->OnHistoryProgressed.BindUObject(this, &UPreloadsService::StartPreload);
}

void UPreloadsService::StartPreload(TSet<FName> InPreloadIds, FOnPreloadCompleted Callback)
{
	ScreensService->Open<ULoadingScreen>();
	
	CurrentPathsById.Empty();

	HistoryPreloadIds = InPreloadIds;
	
	for (auto Config : PreloadConfigs)
	{
		TMap<FName, FSoftObjectPath> ConfigPaths = Config->GetSoftPaths();
		
		for (const auto& [Id, Path] : ConfigPaths)
		{
			if (HistoryPreloadIds.Contains(Id))
			{
				CurrentPathsById.Add(Id, Path);
			}
		}
	}

	int32 PathsCount = CurrentPathsById.Num();
	if (PathsCount == 0)
	{
		CompletePreload(Callback);
		return;
	}

	for (const auto& Path : CurrentPathsById)
	{
		AssetsService->LoadAsync(Path.Key, Path.Value,
			FStreamableDelegate::CreateLambda([this, &PathsCount, Callback]
			{
				if ((PathsCount--) == 0)
				{
					CompletePreload(Callback);
				}
			}));
	}
}

void UPreloadsService::CompletePreload(const FOnPreloadCompleted& Callback)
{
	ScreensService->Close();
	
	Callback.Execute();
}

void UPreloadsService::Release()
{
	for (auto Id : HistoryPreloadIds)
	{
		if (auto Asset = AssetsService->HandlesById.FindRef(Id))
		{
			if (Asset)
			{
				Asset->ReleaseHandle();
			}
			AssetsService->HandlesById.Remove(Id);
		}
	}
}
