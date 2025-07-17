// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Handlerable.h"
#include "GameFramework/Actor.h"
#include "VeilOfFaith/EditorUtils/CustomId.h"
#include "VeilOfFaith/Fragments/Base/FragmentMacros.h"
#include "VeilOfFaith/Services/Base/Fragmentable.h"
#include "ActorHandler.generated.h"

UCLASS()
class VEILOFFAITH_API AActorHandler : public AActor,
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
