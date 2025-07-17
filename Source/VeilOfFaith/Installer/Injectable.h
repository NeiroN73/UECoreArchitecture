// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Injectable.generated.h"

class UInstallerContainer;

UINTERFACE()
class UInjectable : public UInterface
{
	GENERATED_BODY()
};

class VEILOFFAITH_API IInjectable
{
	GENERATED_BODY()

public:
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) = 0;
};
