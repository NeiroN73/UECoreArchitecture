// Copyright Floruit, Inc. All Rights Reserved.


#include "CharacterHandler.h"

#include "ProjectCoreRuntime/Fragments/DialogueFragment.h"
#include "ProjectCoreRuntime/Fragments/InteractFragment.h"


FName ACharacterHandler::GetParticipantName_Implementation() const
{
	return Id;
}

ACharacterHandler::ACharacterHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACharacterHandler::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
}

void ACharacterHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterHandler::BuildFragments(UFragmentsFactory* InFragmentsFactory)
{
	InitializeFragmentable(InFragmentsFactory);

	if (Controller)
	{
		if (auto Fragment = TryAddFragment<UInteractFragment>())
		{
			Fragment->Initialize(this, Controller);
		}
	}
}

FName ACharacterHandler::GetId()
{
	return Id;
}
