// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/HistoryCondition.h"
#include "EmptyCondition.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UEmptyCondition : public UHistoryCondition
{
	GENERATED_BODY()

public:
	virtual void Check() override;
};
