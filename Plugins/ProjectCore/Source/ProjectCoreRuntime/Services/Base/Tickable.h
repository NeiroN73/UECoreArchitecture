// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Tickable.generated.h"

UINTERFACE()
class UTickable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API ITickable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Tick(float DeltaSeconds) = 0;
};
