// Copyright Floruit, Inc. All Rights Reserved.


#include "ActorHandler.h"


AActorHandler::AActorHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AActorHandler::BuildFragments(UFragmentsFactory* NewModuleFactory)
{
	ModuleFactory = NewModuleFactory;
}

FName AActorHandler::GetId()
{
	return Id;
}
