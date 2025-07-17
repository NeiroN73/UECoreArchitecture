// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractParams.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class VEILOFFAITH_API IInteractable
{
	GENERATED_BODY()

public:
	virtual bool TryInteract(TSharedPtr<FInteractParams> Params = MakeShared<FInteractParams>()) = 0;
};
