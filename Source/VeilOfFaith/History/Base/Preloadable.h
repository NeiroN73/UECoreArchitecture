// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Preloadable.generated.h"

UINTERFACE()
class UPreloadable : public UInterface
{
	GENERATED_BODY()
};

class VEILOFFAITH_API IPreloadable
{
	GENERATED_BODY()

public:
	virtual TArray<FName> GetPreloadIds() = 0;
};
