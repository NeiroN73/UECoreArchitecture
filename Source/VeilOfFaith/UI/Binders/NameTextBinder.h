// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Binder.h"
#include "Base/BinderDelegates.h"
#include "NameTextBinder.generated.h"

class UTextBlock;

UCLASS()
class VEILOFFAITH_API UNameTextBinder : public UBinder
{
	GENERATED_BODY()

public:
	FOnFNameChanged OnBinderTriggered;
	void Bind(UTextBlock* TextBlock, const FName& Value);
};
