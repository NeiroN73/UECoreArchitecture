// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DlgSystem/DlgDialogueParticipant.h"
#include "GameFramework/Character.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "ProjectCoreRuntime/Handlers/Base/Handlerable.h"
#include "ProjectCoreRuntime/Fragments/Base/FragmentMacros.h"
#include "ProjectCoreRuntime/Services/Base/Fragmentable.h"
#include "ProjectCoreRuntime/TableConfigs/CharactersTableData.h"
#include "CharacterHandler.generated.h"

class UDlgDialogue;

UCLASS()
class PROJECTCORERUNTIME_API ACharacterHandler : public ACharacter,
public IDlgDialogueParticipant,
public IHandlerable,
public IFragmentable
{
	GENERATED_BODY()
	FRAGMENTABLE_BODY()

private:
	FName GetParticipantName_Implementation() const override;

public:
	UPROPERTY(EditAnywhere, Category="Id")
	FCustomId Id;
	
	FCharactersTableData* Data;

	ACharacterHandler();

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BuildFragments(UFragmentsFactory* InFragmentsFactory) override;

private:
	virtual FName GetId() override;
};
