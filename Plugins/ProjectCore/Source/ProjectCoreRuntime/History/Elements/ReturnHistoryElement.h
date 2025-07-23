// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseHistoryElement.h"
#include "ReturnHistoryElement.generated.h"

class UHistoryElement;

UCLASS()
class PROJECTCORERUNTIME_API UReturnHistoryElement : public UBaseHistoryElement
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UBaseHistoryElement> ParentElement;

	void Execute();
};
