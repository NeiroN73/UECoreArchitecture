// Copyright Floruit, Inc. All Rights Reserved.


#include "DialogueOptionView.h"

#include "DialogueOptionViewModel.h"
#include "ProjectCoreRuntime/Factories/ViewModelsFactory.h"


void UDialogueOptionView::BuildViewModel(UViewModelsFactory* ViewModelFactory)
{
	ViewModel = ViewModelFactory->Create<UDialogueOptionViewModel>();

	BIND_TO_VIEW(AnswerText, UTextBinder, FText)
	BIND_FROM_VIEW(NextButton, UButtonBinder)
}
