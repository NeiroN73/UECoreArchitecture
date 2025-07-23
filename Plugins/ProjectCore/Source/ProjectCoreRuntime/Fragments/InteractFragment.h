// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/CharacterFragment.h"
#include "ProjectCoreRuntime/Handlers/Base/InteractParams.h"
#include "InteractFragment.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteracted, FName)

UCLASS()
class PROJECTCORERUNTIME_API UInteractFragment : public UCharacterFragment
{
	GENERATED_BODY()

public:
	FOnInteracted OnInteracted;
	
	virtual void Initialize(ACharacter* pCharacter, AController* pController) override;
	bool TryInteract(TSharedPtr<FInteractParams> Params = MakeShared<FInteractParams>());
};
