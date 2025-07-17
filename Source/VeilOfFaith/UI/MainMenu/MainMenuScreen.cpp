// Copyright Floruit, Inc. All Rights Reserved.


#include "MainMenuScreen.h"

#include "MainMenuViewModel.h"
#include "VeilOfFaith/Factories/ViewModelsFactory.h"
#include "VeilOfFaith/UI/Base/MvvmMacros.h"
#include "VeilOfFaith/UI/Binders/ButtonBinder.h"

void UMainMenuScreen::BuildViewModel(UViewModelsFactory* ViewModelFactory)
{
	auto ViewModel = ViewModelFactory->Create<UMainMenuViewModel>();

	//BIND_FROM_VIEW(ContinueButton, UButtonBinder);

	ViewModel->Bind();
}
