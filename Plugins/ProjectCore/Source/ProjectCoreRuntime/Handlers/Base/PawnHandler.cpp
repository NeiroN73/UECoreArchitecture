// Copyright Floruit, Inc. All Rights Reserved.


#include "PawnHandler.h"


APawnHandler::APawnHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APawnHandler::BuildFragments(UFragmentsFactory* NewModuleFactory)
{
	InitializeFragmentable(NewModuleFactory);
}

FName APawnHandler::GetId()
{
	return Id;
}
