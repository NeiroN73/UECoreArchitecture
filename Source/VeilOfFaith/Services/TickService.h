// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "Base/Tickable.h"
#include "TickService.generated.h"

class UFragmentsFactory;

UCLASS()
class VEILOFFAITH_API UTickService : public UService,
public ITickable
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	void RegisterTick(ITickable* Tickable);

private:
	TArray<ITickable*> Tickables;
};
