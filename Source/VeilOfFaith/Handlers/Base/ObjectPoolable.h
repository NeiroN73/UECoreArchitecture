// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UObjectPoolable : public UInterface
{
	GENERATED_BODY()
};

class VEILOFFAITH_API IObjectPoolable
{
	GENERATED_BODY()

public:
	virtual void Get() {}
	virtual void Return() {}
	virtual void Release() {}
};
