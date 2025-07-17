// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractParams.generated.h"

USTRUCT()
struct VEILOFFAITH_API FInteractParams
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<APawn> Pawn;
	UPROPERTY()
	TObjectPtr<ACharacter> Character;
	UPROPERTY()
	TObjectPtr<ACharacter> Invoker;
	
	FInteractParams()
		: Pawn(nullptr), Character(nullptr), Invoker(nullptr) {}
	
	~FInteractParams() = default;
};
