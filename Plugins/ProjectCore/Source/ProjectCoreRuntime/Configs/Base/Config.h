// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectCoreRuntime/Installer/Worldable.h"
#include "Config.generated.h"

UCLASS(Abstract)
class PROJECTCORERUNTIME_API UConfig : public UDataAsset,
public IWorldable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UWorld> World;
	
	virtual void WorldChanged(UWorld* InWorld) override;
};
