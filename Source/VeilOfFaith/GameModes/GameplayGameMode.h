// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerGameMode.h"
#include "GameplayGameMode.generated.h"

UCLASS()
class VEILOFFAITH_API AGameplayGameMode : public AInstallerGameMode
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
};
