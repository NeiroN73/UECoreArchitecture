// Copyright Floruit, Inc. All Rights Reserved.


#include "DialogueScreen.h"

#include "DialogueViewModel.h"
#include "VeilOfFaith/Factories/ViewModelsFactory.h"
#include "VeilOfFaith/UI/Base/MvvmMacros.h"
#include "VeilOfFaith/UI/Binders/NameTextBinder.h"

void UDialogueScreen::BuildViewModel(UViewModelsFactory* ViewModelFactory)
{
	auto ViewModel = ViewModelFactory->Create<UDialogueViewModel>();

	BIND_TO_VIEW(CharacterName, UNameTextBinder, FName)
	BIND_TO_VIEW(PhraseText, UTextBinder, FText)
	
	ViewModel->Bind(OptionsContainer, OptionClass);
}
