// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ScreensService.h"
#include "Base/Service.h"
#include "VeilOfFaith/Configs/LevelsConfig.h"
#include "VeilOfFaith/Installer/Injectable.h"
#include "LevelsService.generated.h"

UCLASS()
class VEILOFFAITH_API ULevelsService : public UService,
public IInjectable
{
	GENERATED_BODY()

public:
	void LoadLevelAsync(TSoftObjectPtr<UWorld> Level, FStreamableDelegate Callback);
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	TObjectPtr<ULevelsConfig> GetLevelsConfig();

private:
	UPROPERTY()
	TObjectPtr<UScreensService> ViewsService;

	UPROPERTY()
	TObjectPtr<ULevelsConfig> LevelsConfig;

	UPROPERTY()
	TObjectPtr<UAssetsService> AssetsService;
}; 
