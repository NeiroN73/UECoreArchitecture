// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Worldable.generated.h"

UINTERFACE()
class UWorldable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IWorldable
{
	GENERATED_BODY()

public:
	virtual void WorldChanged(UWorld* NewWorld) = 0;
};
