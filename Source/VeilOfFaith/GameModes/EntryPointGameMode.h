// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerGameMode.h"
#include "EntryPointGameMode.generated.h"

UCLASS()
class VEILOFFAITH_API AEntryPointGameMode : public AInstallerGameMode
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
