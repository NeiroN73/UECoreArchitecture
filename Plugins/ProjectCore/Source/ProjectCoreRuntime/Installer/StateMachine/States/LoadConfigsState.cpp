// Copyright Floruit, Inc. All Rights Reserved.


#include "LoadConfigsState.h"

#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Services/AssetsLoader.h"

void ULoadConfigsState::Enter()
{
	if (StateMachine)
	{
		StateMachine->AssetsLoaderService = NewObject<UAssetsService>();
		
		FPrimaryAssetType PrimaryAssetType = FPrimaryAssetType(FName("Configs"));
		FPrimaryAssetId PrimaryAssetId = FPrimaryAssetId(PrimaryAssetType, FName("PDA_Configs"));
		StateMachine->LoadedConfigsHandler = StateMachine->AssetsLoaderService->LoadPrimaryAsync(PrimaryAssetId,
			FStreamableDelegate::CreateLambda([this]
		{
				StateMachine->NextState();
		}));
	}
}
