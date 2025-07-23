// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "ProjectCoreRuntime/UI/Base/Screen.h"
#include "ProjectCoreRuntime/UI/Base/View.h"
#include "MainMenuScreen.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UMainMenuScreen : public UScreen
{
	GENERATED_BODY()

public:
	virtual void BuildViewModel(UViewModelsFactory* ViewModelFactory) override;

private:
	UPROPERTY(meta= (BindWidget))
	UButton* ContinueButton;
};
