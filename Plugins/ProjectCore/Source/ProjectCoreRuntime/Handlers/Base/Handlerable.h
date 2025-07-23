// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Handlerable.generated.h"

UINTERFACE()
class UHandlerable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IHandlerable
{
	GENERATED_BODY()

public:
	virtual FName GetId() = 0;
};
