// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Handlerable.h"
#include "GameFramework/Actor.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentMacros.h"
#include "ProjectCoreRuntime/Services/Base/Fragmentable.h"
#include "ActorHandler.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API AActorHandler : public AActor,
public IHandlerable,
public IFragmentable
{
	GENERATED_BODY()
	FRAGMENTABLE_BODY()

private:
	UPROPERTY()
	TObjectPtr<UFragmentsFactory> ModuleFactory;
	
public:
	AActorHandler();
	virtual void BuildFragments(UFragmentsFactory* NewModuleFactory) override;

private:
	virtual FName GetId() override;

public:
	UPROPERTY(EditAnywhere, Category="Id")
	FCustomId Id;
};
