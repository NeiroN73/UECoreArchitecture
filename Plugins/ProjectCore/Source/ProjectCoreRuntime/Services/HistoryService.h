// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "HistoryService.generated.h"

class UPreloadsService;
class UHistorySaveState;
class UHistoryConfig;
class UDialoguesService;

DECLARE_DELEGATE(FOnHistoryProgressed)

UCLASS()
class PROJECTCORERUNTIME_API UHistoryService : public UService,
public IInjectable
{
	GENERATED_BODY()

public:
	virtual void Inject(TObjectPtr<UInstallerContainer> InContainer) override;

	void TryProgress();
	void OnPreloadsLoaded();

private:
	UPROPERTY()
	TObjectPtr<UHistorySaveState> HistorySaveState;

	UPROPERTY()
	TObjectPtr<UInstallerContainer> Container;
	UPROPERTY()
	TObjectPtr<UDialoguesService> DialoguesService;
	UPROPERTY()
	TObjectPtr<UHistoryConfig> HistoryConfig;
	UPROPERTY()
	TObjectPtr<UPreloadsService> PreloadsService;

public:
	FOnHistoryProgressed OnHistoryProgressed;
};
