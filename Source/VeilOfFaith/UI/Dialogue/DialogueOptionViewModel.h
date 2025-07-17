// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VeilOfFaith/Installer/Injectable.h"
#include "VeilOfFaith/UI/Base/MvvmMacros.h"
#include "VeilOfFaith/UI/Base/ViewModel.h"
#include "VeilOfFaith/UI/Binders/ButtonBinder.h"
#include "VeilOfFaith/UI/Binders/TextBinder.h"
#include "DialogueOptionViewModel.generated.h"

class UScreensService;
class UDialoguesService;

UCLASS()
class VEILOFFAITH_API UDialogueOptionViewModel : public UViewModel,
public IInjectable
{
	GENERATED_BODY()

public:
	BIND_FROM_VIEW_MODEL(FText, AnswerText, UTextBinder)
	BIND_TO_VIEW_MODEL(NextButton, UButtonBinder)

	void Bind();
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;

	UPROPERTY()
	int32 OptionIndex;

private:
	UPROPERTY()
	TObjectPtr<UDialoguesService> DialoguesService;

	void ProgressDialogue();
	void UpdateData();
};
