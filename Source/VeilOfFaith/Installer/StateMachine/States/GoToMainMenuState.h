// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "UObject/Object.h"
#include "VeilOfFaith/Services/LevelsService.h"
#include "GoToMainMenuState.generated.h"

UCLASS()
class VEILOFFAITH_API UGoToMainMenuState : public UInstallerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;

private:
	UPROPERTY()
	TObjectPtr<ULevelsService> LevelsService;
	UPROPERTY()
	TObjectPtr<UAssetsService> AssetsLoaderService;
};
