// Copyright Floruit, Inc. All Rights Reserved.


#include "ActorHandler.h"


AActorHandler::AActorHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AActorHandler::BuildFragments(UFragmentsFactory* InFragmentsFactory)
{
	InitializeFragmentable(InFragmentsFactory);
}

FName AActorHandler::GetId()
{
	return Id;
}
