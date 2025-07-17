// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "UObject/Object.h"
#include "LoadConfigsState.generated.h"

UCLASS()
class VEILOFFAITH_API ULoadConfigsState : public UInstallerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
};
