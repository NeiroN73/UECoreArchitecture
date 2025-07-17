// Copyright Floruit, Inc. All Rights Reserved.


#include "PawnHandler.h"


APawnHandler::APawnHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APawnHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APawnHandler::BuildFragments(UFragmentsFactory* NewModuleFactory)
{
	ModuleFactory = NewModuleFactory;
}

FName APawnHandler::GetId()
{
	return Id;
}
