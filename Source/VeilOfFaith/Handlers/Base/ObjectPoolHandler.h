// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActorHandler.h"
#include "ObjectPoolable.h"
#include "ObjectPoolHandler.generated.h"

UCLASS(Abstract)
class VEILOFFAITH_API AObjectPoolHandler : public AActorHandler,
public IObjectPoolable
{
	GENERATED_BODY()

public:
	AObjectPoolHandler();
	virtual void Get() override;
	virtual void Return() override;
	virtual void Release() override;
};
