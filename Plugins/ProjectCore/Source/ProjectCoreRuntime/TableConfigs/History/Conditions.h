// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Conditions.generated.h"

UENUM(BlueprintType)
enum class EConditions : uint8
{
	And,
	Or
};
