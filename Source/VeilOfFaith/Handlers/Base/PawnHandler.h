// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Handlerable.h"
#include "GameFramework/Pawn.h"
#include "VeilOfFaith/EditorUtils/CustomId.h"
#include "VeilOfFaith/Fragments/Base/FragmentMacros.h"
#include "VeilOfFaith/Services/Base/Fragmentable.h"
#include "PawnHandler.generated.h"

class UFragmentsFactory;

UCLASS()
class VEILOFFAITH_API APawnHandler : public APawn,
public IHandlerable,
public IFragmentable
{
	GENERATED_BODY()
	FRAGMENTABLE_BODY()

private:
	UPROPERTY()
	TObjectPtr<UFragmentsFactory> ModuleFactory;

public:
	UPROPERTY(EditAnywhere, Category="Id")
	FCustomId Id;

	APawnHandler();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BuildFragments(UFragmentsFactory* NewModuleFactory) override;
	virtual FName GetId() override;
};
