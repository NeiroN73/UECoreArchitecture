// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VeilOfFaith/UI/Base/View.h"

#include "DialogueOptionView.generated.h"

class UDialogueOptionViewModel;
class UButton;
class UTextBlock;

UCLASS()
class VEILOFFAITH_API UDialogueOptionView : public UUserWidget, public IView
{
	GENERATED_BODY()

public:
	virtual void BuildViewModel(UViewModelsFactory* ViewModelFactory) override;

	TObjectPtr<UDialogueOptionViewModel> ViewModel;

private:
	UPROPERTY(meta= (BindWidget))
	UTextBlock* AnswerText;
	UPROPERTY(meta= (BindWidget))
	UButton* NextButton;
};
