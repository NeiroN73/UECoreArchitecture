// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/TableData.h"
#include "CharactersTableData.generated.h"

class ACharacterHandler;

USTRUCT()
struct VEILOFFAITH_API FCharactersTableData : public FTableData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacterHandler> Class;
};