// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Initializable.generated.h"

UINTERFACE()
class UInitializable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IInitializable
{
	GENERATED_BODY()

public:
	virtual void Initialize() = 0;
};
