// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VeilOfFaith/UI/Base/Screen.h"
#include "VeilOfFaith/UI/Base/View.h"
#include "BoardScreen.generated.h"

class UBoardViewModel;
class UButton;

UCLASS()
class VEILOFFAITH_API UBoardScreen : public UScreen
{
	GENERATED_BODY()

public:
	virtual void BuildViewModel(UViewModelsFactory* ViewModelFactory) override;

	TObjectPtr<UBoardViewModel> ViewModel;
	
private:
	UPROPERTY(meta= (BindWidget))
	UButton* MyButton;
};
