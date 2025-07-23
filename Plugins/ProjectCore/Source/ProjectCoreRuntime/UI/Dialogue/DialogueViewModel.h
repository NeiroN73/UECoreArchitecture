// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "ProjectCoreRuntime/UI/Base/MvvmMacros.h"
#include "ProjectCoreRuntime/UI/Base/ViewModel.h"
#include "ProjectCoreRuntime/UI/Binders/ButtonBinder.h"
#include "ProjectCoreRuntime/UI/Binders/NameTextBinder.h"
#include "ProjectCoreRuntime/UI/Binders/TextBinder.h"
#include "DialogueViewModel.generated.h"

class UDialogueOptionViewModel;
class UDialogueOptionView;
class UViewsFactory;
class UScreensFactory;
class UPanelWidget;
class UDialoguesService;

UCLASS()
class PROJECTCORERUNTIME_API UDialogueViewModel : public UViewModel,
public IInjectable
{
	GENERATED_BODY()

	BIND_FROM_VIEW_MODEL(FName, CharacterName, UNameTextBinder)
	BIND_FROM_VIEW_MODEL(FText, PhraseText, UTextBinder)

public:
	void Bind(UPanelWidget* InOptionsContainer, TSubclassOf<UDialogueOptionView> InOptionClass);
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;

private:
	UPROPERTY()
	TObjectPtr<UDialoguesService> DialoguesService;
	UPROPERTY()
	TObjectPtr<UViewsFactory> ViewsFactory;

	UPROPERTY()
	TArray<TObjectPtr<UDialogueOptionView>> OptionViews;
	
	UPROPERTY()
	TWeakObjectPtr<UPanelWidget> OptionsContainer;
	UPROPERTY()
	TSubclassOf<UDialogueOptionView> OptionClass;

	void UpdateData();
};
