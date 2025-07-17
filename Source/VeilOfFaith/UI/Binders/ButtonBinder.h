// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Binder.h"
#include "ButtonBinder.generated.h"

class UButton;

UCLASS()
class VEILOFFAITH_API UButtonBinder : public UBinder
{
	GENERATED_BODY()

public:
	FSimpleDelegate OnBinderTriggered;
	
	void Bind(UButton* Button);

private:
	UFUNCTION()
	void ButtonClicked();
};
