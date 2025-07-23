// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerGameMode.h"
#include "UObject/Object.h"
#include "MainMenuGameMode.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API AMainMenuGameMode : public AInstallerGameMode
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
