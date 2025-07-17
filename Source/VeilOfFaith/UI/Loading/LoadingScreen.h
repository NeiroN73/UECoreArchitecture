// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VeilOfFaith/UI/Base/Screen.h"
#include "LoadingScreen.generated.h"

UCLASS()
class VEILOFFAITH_API ULoadingScreen : public UScreen
{
	GENERATED_BODY()

public:
	virtual void BuildViewModel(UViewModelsFactory* ViewModelFactory) override {}
};
