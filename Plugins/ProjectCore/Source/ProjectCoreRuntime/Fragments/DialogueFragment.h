// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/CharacterFragment.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "DialogueFragment.generated.h"

class UScreensService;
class UHandlersService;
class UDlgContext;
class UDlgDialogue;
class UDialoguesService;

UCLASS()
class PROJECTCORERUNTIME_API UDialogueFragment : public UCharacterFragment,
public IInjectable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UDialoguesService> DialogueService;
	UPROPERTY()
	TObjectPtr<UHandlersService> CharactersService;
	UPROPERTY()
	TObjectPtr<UScreensService> ScreensService;

	UPROPERTY()
	TObjectPtr<UDlgDialogue> CurrentDialogue;
	UPROPERTY()
	TObjectPtr<UDlgContext> CurrentContext;

	void StartDialogue();
	
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
};
