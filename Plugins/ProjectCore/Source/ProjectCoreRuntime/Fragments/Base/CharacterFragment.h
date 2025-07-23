// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Fragment.h"
#include "CharacterFragment.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UCharacterFragment : public UFragment
{
	GENERATED_BODY()

public:
	virtual void Initialize(ACharacter* pCharacter, AController* pController);

protected:
	UPROPERTY()
	TObjectPtr<ACharacter> Character;
	UPROPERTY()
	TObjectPtr<AController> Controller;
};
