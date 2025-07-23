// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/InstallerStateMachine.h"
#include "InstallerGameSubsystem.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UInstallerGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UInstallerStateMachine> StateMachine;
};
