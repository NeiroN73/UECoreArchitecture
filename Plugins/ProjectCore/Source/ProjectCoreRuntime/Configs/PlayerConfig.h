// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "Engine/DataAsset.h"
#include "PlayerConfig.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UPlayerConfig : public UConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 MoveSpeed;
};
