// Copyright Floruit, Inc. All Rights Reserved.


#include "CharacterHandler.h"


ACharacterHandler::ACharacterHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

FName ACharacterHandler::GetId()
{
	return Id;
}
