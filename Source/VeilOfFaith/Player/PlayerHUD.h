// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

UCLASS()
class VEILOFFAITH_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
