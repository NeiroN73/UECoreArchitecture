// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetsLoader.h"
#include "Base/Service.h"
#include "VeilOfFaith/Installer/Initializable.h"
#include "VeilOfFaith/Installer/Injectable.h"
#include "PreloadsService.generated.h"

class UScreensService;
class UConfig;
class IPreloadConfig;
class UAssetsService;
class UHistoryService;
class IPreloadable;
class UHistorySaveState;

DECLARE_DELEGATE(FOnPreloadCompleted)

UCLASS()
class VEILOFFAITH_API UPreloadsService : public UService,
public IInjectable,
public IInitializable
{
	GENERATED_BODY()

public:
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	virtual void Initialize() override;

	void StartPreload(TSet<FName> InPreloadIds, FOnPreloadCompleted Callback);
	void CompletePreload(const FOnPreloadCompleted& Callback);
	void Release();

	template<class TObject = UObject>
	TObject* GetLoadedAsset(FName Id)
	{
		return AssetsService->GetLoadedAsset<TObject>(Id);
	}

private:
	UPROPERTY()
	TObjectPtr<UAssetsService> AssetsService;
	UPROPERTY()
	TObjectPtr<UScreensService> ScreensService;
	
	TArray<IPreloadConfig*> PreloadConfigs;
	
	UPROPERTY()
	TSet<FName> HistoryPreloadIds;
	UPROPERTY()
	TMap<FName, FSoftObjectPath> CurrentPathsById;
};
