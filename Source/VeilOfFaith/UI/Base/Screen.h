// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "View.h"
#include "Blueprint/UserWidget.h"
#include "Screen.generated.h"

UCLASS(Abstract)
class VEILOFFAITH_API UScreen : public UUserWidget, public IView
{
	GENERATED_BODY()

public:
	virtual void BuildViewModel(UViewModelsFactory* ViewModelFactory) override {}
};
