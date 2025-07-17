// Copyright Floruit, Inc. All Rights Reserved.


#include "ButtonBinder.h"

#include "Components/Button.h"

void UButtonBinder::Bind(UButton* Button)
{
	Button->OnClicked.AddDynamic(this, &UButtonBinder::ButtonClicked);
}

void UButtonBinder::ButtonClicked()
{
	OnBinderTriggered.ExecuteIfBound();
}
