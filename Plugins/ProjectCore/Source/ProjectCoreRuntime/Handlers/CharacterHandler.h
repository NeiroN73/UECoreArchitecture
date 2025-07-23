// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "ProjectCoreRuntime/Handlers/Base/Handlerable.h"
#include "ProjectCoreRuntime/TableConfigs/CharactersTableData.h"
#include "CharacterHandler.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API ACharacterHandler : public ACharacter,
public IHandlerable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Id")
	FCustomId Id;
	
	FCharactersTableData* Data;

	ACharacterHandler();

private:
	virtual FName GetId() override;
};
