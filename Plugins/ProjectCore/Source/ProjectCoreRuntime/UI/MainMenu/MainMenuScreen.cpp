// Copyright Floruit, Inc. All Rights Reserved.


#include "MainMenuScreen.h"

#include "MainMenuViewModel.h"
#include "ProjectCoreRuntime/Factories/ViewModelsFactory.h"
#include "ProjectCoreRuntime/UI/Base/MvvmMacros.h"
#include "ProjectCoreRuntime/UI/Binders/ButtonBinder.h"

void UMainMenuScreen::BuildViewModel(UViewModelsFactory* ViewModelFactory)
{
	auto ViewModel = ViewModelFactory->Create<UMainMenuViewModel>();

	//BIND_FROM_VIEW(ContinueButton, UButtonBinder);

	ViewModel->Bind();
}
