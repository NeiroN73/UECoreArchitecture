// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/UI/Base/Screen.h"
#include "LoadingScreen.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API ULoadingScreen : public UScreen
{
	GENERATED_BODY()

public:
	virtual void BuildViewModel(UViewModelsFactory* ViewModelFactory) override {}
};
