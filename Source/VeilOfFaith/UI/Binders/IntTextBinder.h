// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Binder.h"
#include "Base/BinderDelegates.h"
#include "IntTextBinder.generated.h"

class UTextBlock;

UCLASS()
class VEILOFFAITH_API UIntTextBinder : public UBinder
{
	GENERATED_BODY()

public:
	FOnint32Changed OnBinderTriggered;
	void Bind(UTextBlock* TextBlock, const int32& Value);
};
