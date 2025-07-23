// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "View.generated.h"

class UViewModelsFactory;

UINTERFACE()
class UView : public UInterface
{
	GENERATED_BODY()
};

class PROJECTCORERUNTIME_API IView
{
	GENERATED_BODY()

public:
	virtual void BuildViewModel(UViewModelsFactory* ViewModelFactory) = 0;
};
