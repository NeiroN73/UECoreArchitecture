// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/UI/Base/Screen.h"
#include "DialogueScreen.generated.h"

class UDialogueOptionView;
class UTextBlock;
class UButton;

UCLASS()
class PROJECTCORERUNTIME_API UDialogueScreen : public UScreen
{
	GENERATED_BODY()

public:
	virtual void BuildViewModel(UViewModelsFactory* ViewModelFactory) override;

private:
	UPROPERTY(meta= (BindWidget))
	UTextBlock* CharacterName;
	UPROPERTY(meta= (BindWidget))
	UTextBlock* PhraseText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPanelWidget> OptionsContainer;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDialogueOptionView> OptionClass;
};
