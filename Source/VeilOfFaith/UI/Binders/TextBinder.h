// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Binder.h"
#include "Base/BinderDelegates.h"
#include "TextBinder.generated.h"

class UTextBlock;

UCLASS()
class VEILOFFAITH_API UTextBinder : public UBinder
{
	GENERATED_BODY()

public:
	FOnFTextChanged OnBinderTriggered;
	void Bind(UTextBlock* TextBlock, const FText& Value);
};
