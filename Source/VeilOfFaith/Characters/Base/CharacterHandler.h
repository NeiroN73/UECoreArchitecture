// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DlgSystem/DlgDialogueParticipant.h"
#include "GameFramework/Character.h"
#include "VeilOfFaith/EditorUtils/CustomId.h"
#include "VeilOfFaith/Handlers/Base/Handlerable.h"
#include "VeilOfFaith/Fragments/Base/FragmentMacros.h"
#include "VeilOfFaith/Services/Base/Fragmentable.h"
#include "VeilOfFaith/TableConfigs/CharactersTableData.h"
#include "CharacterHandler.generated.h"

class UDlgDialogue;

UCLASS()
class VEILOFFAITH_API ACharacterHandler : public ACharacter,
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
