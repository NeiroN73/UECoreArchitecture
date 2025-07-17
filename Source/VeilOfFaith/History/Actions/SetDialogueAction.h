// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/HistoryAction.h"
#include "VeilOfFaith/EditorUtils/CustomId.h"
#include "VeilOfFaith/History/Base/Preloadable.h"
#include "SetDialogueAction.generated.h"

class ACharacterHandler;
class UDialoguesService;
class UInstallerContainer;
class UDlgDialogue;

UCLASS()
class VEILOFFAITH_API USetDialogueAction : public UHistoryAction,
public IPreloadable
{
	GENERATED_BODY()

public:
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void Execute() override;

	UPROPERTY(EditAnywhere)
	FCustomId CharacterId;
	
	UPROPERTY(EditAnywhere)
	FCustomId DialogueId;
	
private:
	UPROPERTY()
	TObjectPtr<UDialoguesService> DialoguesService;

public:
	virtual TArray<FName> GetPreloadIds() override;
};
