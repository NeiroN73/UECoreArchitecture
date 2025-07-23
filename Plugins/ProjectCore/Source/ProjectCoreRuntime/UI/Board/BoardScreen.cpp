// Copyright Floruit, Inc. All Rights Reserved.


#include "BoardScreen.h"

#include "BoardViewModel.h"
#include "ProjectCoreRuntime/Factories/ViewModelsFactory.h"
#include "ProjectCoreRuntime/UI/Base/MvvmMacros.h"
#include "ProjectCoreRuntime/UI/Binders/ButtonBinder.h"

void UBoardScreen::BuildViewModel(UViewModelsFactory* ViewModelFactory)
{
	ViewModel = ViewModelFactory->Create<UBoardViewModel>();

	//BIND_FROM_VIEW(MyButton, UButtonBinder)
	
	ViewModel->Initialize();
}
