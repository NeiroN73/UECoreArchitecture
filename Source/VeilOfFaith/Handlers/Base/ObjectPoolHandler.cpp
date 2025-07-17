// Copyright Floruit, Inc. All Rights Reserved.


#include "ObjectPoolHandler.h"


AObjectPoolHandler::AObjectPoolHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AObjectPoolHandler::Get()
{
	IObjectPoolable::Get();
}

void AObjectPoolHandler::Return()
{
	IObjectPoolable::Return();
}

void AObjectPoolHandler::Release()
{
	IObjectPoolable::Release();
}
