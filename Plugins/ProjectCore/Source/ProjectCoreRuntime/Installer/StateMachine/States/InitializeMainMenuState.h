// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "InitializeMainMenuState.generated.h"

class UScreensService;

UCLASS()
class PROJECTCORERUNTIME_API UInitializeMainMenuState : public UInstallerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;

private:
	UPROPERTY()
	TObjectPtr<UScreensService> ViewsService;
};
