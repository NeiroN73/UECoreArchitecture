// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VeilOfFaith/GameModes/Base/InstallerGameMode.h"
#include "InstallerStateMachine.generated.h"

class UAssetsService;
struct FStreamableHandle;
class UInstallerContainer;
class UInstallerState;

UCLASS()
class VEILOFFAITH_API UInstallerStateMachine : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TObjectPtr<UAssetsService> AssetsLoaderService;
	TSharedPtr<FStreamableHandle> LoadedConfigsHandler;
	
	void Initialize(TArray<UInstallerState*> NewStates);
	void Tick(float DeltaSeconds);
	void NextState();

private:
	TQueue<TObjectPtr<UInstallerState>> States;
	UPROPERTY()
	TObjectPtr<UInstallerState> CurrentState;
};
