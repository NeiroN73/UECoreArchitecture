// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Binder.h"
#include "UObject/Object.h"
#include "Base/BinderDelegates.h"
#include "StringTextBinder.generated.h"

class UTextBlock;

UCLASS()
class VEILOFFAITH_API UStringTextBinder : public UBinder
{
	GENERATED_BODY()
	
public:
	FOnFStringChanged OnBinderTriggered;
	void Bind(UTextBlock* TextBlock, const FString& Value);
};
