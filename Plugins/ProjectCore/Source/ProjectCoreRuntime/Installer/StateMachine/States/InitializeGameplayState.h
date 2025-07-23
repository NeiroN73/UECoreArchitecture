// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "UObject/Object.h"
#include "InitializeGameplayState.generated.h"

class UHandlersFactory;
class UScreensService;

UCLASS()
class PROJECTCORERUNTIME_API UInitializeGameplayState : public UInstallerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
};
