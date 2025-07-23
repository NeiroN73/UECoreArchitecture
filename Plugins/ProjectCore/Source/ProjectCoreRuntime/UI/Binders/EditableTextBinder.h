// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Binder.h"
#include "Base/BinderDelegates.h"
#include "UObject/Object.h"
#include "Components/EditableText.h"
#include "EditableTextBinder.generated.h"

class UEditableText;

UCLASS()
class PROJECTCORERUNTIME_API UEditableTextBinder : public UBinder
{
	GENERATED_BODY()

public:
	FOnFStringChanged OnBinderTriggered;
	
	void Bind(TObjectPtr<UEditableText> EditableText);

	UFUNCTION()
	void OnTextChanged(const FText& Text);
};
