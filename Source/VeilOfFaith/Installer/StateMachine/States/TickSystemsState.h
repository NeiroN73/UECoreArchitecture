// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "TickSystemsState.generated.h"

class UTickService;

UCLASS()
class VEILOFFAITH_API UTickSystemsState : public UInstallerState
{
	GENERATED_BODY()

public:
	virtual void Enter() override;
	virtual void Tick(float DeltaSeconds) override;

	TObjectPtr<UTickService> TickService;
};
