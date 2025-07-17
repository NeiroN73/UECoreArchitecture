// Copyright Floruit, Inc. All Rights Reserved.


#include "BoardScreen.h"

#include "BoardViewModel.h"
#include "VeilOfFaith/Factories/ViewModelsFactory.h"
#include "VeilOfFaith/UI/Base/MvvmMacros.h"
#include "VeilOfFaith/UI/Binders/ButtonBinder.h"

void UBoardScreen::BuildViewModel(UViewModelsFactory* ViewModelFactory)
{
	ViewModel = ViewModelFactory->Create<UBoardViewModel>();

	//BIND_FROM_VIEW(MyButton, UButtonBinder)
	
	ViewModel->Initialize();
}
