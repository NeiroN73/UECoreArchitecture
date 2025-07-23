// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "ProjectCoreRuntime/UI/Base/MvvmMacros.h"
#include "ProjectCoreRuntime/UI/Base/ViewModel.h"
#include "ProjectCoreRuntime/UI/Binders/ButtonBinder.h"
#include "ProjectCoreRuntime/UI/Binders/TextBinder.h"
#include "DialogueOptionViewModel.generated.h"

class UScreensService;
class UDialoguesService;

UCLASS()
class PROJECTCORERUNTIME_API UDialogueOptionViewModel : public UViewModel,
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
