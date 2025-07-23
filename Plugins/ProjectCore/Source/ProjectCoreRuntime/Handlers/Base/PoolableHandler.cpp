// Copyright Floruit, Inc. All Rights Reserved.


#include "PoolableHandler.h"


APoolableHandler::APoolableHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APoolableHandler::Get()
{
	IObjectPoolable::Get();
}

void APoolableHandler::Return()
{
	IObjectPoolable::Return();
}

void APoolableHandler::Release()
{
	IObjectPoolable::Release();
}
