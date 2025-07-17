// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VeilOfFaith/Installer/Injectable.h"
#include "VeilOfFaith/UI/Base/MvvmMacros.h"
#include "VeilOfFaith/UI/Base/ViewModel.h"
#include "VeilOfFaith/UI/Binders/ButtonBinder.h"
#include "VeilOfFaith/UI/Binders/NameTextBinder.h"
#include "VeilOfFaith/UI/Binders/TextBinder.h"
#include "DialogueViewModel.generated.h"

class UDialogueOptionViewModel;
class UDialogueOptionView;
class UViewsFactory;
class UScreensFactory;
class UPanelWidget;
class UDialoguesService;

UCLASS()
class VEILOFFAITH_API UDialogueViewModel : public UViewModel,
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
