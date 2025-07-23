// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ElementState.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UElementState : public UObject
{
	GENERATED_BODY()

public:
	virtual void Execute() PURE_VIRTUAL(UElementState::Execute)
};
