// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActorHandler.h"
#include "ObjectPoolable.h"
#include "PoolableHandler.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API APoolableHandler : public AActorHandler,
public IObjectPoolable
{
	GENERATED_BODY()

public:
	APoolableHandler();
	virtual void Get() override;
	virtual void Return() override;
	virtual void Release() override;
};
