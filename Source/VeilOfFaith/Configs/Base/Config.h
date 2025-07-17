// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VeilOfFaith/Installer/Worldable.h"
#include "Config.generated.h"

UCLASS(Abstract)
class VEILOFFAITH_API UConfig : public UDataAsset,
public IWorldable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UWorld> World;
	
	virtual void WorldChanged(UWorld* NewWorld) override;
};
