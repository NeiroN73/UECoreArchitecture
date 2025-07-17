// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "VeilOfFaith/Installer/Injectable.h"
#include "DialoguesService.generated.h"

class UDlgContext;
class UScreensService;
class UPreloadsService;
class ACharacterHandler;
class UHandlersService;
class UAssetsService;
class UDialoguesConfig;
class UDlgDialogue;

UCLASS()
class VEILOFFAITH_API UDialoguesService : public UService,
public IInjectable
{
	GENERATED_BODY()

public:
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;

	void StartDialogue(ACharacterHandler* TargetCharacter);
	void SetDialogue(FName CharacterId, FName DialogueId);
	void ProgressDialogue(int32 OptionIndex);
	UDlgContext* GetCurrentContext();

	FSimpleDelegate DialogueProgressed;
	FSimpleDelegate DialogueFinished;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> DialoguesTableConfig;
	UPROPERTY()
	TObjectPtr<UDataTable> CharactersTableConfig;
	UPROPERTY()
	TObjectPtr<UHandlersService> CharactersService;
	UPROPERTY()
	TObjectPtr<UDialoguesConfig> DialoguesConfig;
	UPROPERTY()
	TObjectPtr<UAssetsService> AssetsService;
	UPROPERTY()
	TObjectPtr<UPreloadsService> PreloadsService;
	UPROPERTY()
	TObjectPtr<UScreensService> ScreensService;

	UPROPERTY()
	TObjectPtr<UDlgContext> CurrentContext;
};
