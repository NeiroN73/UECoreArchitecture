// Copyright Floruit, Inc. All Rights Reserved.


#include "ViewsFactory.h"

#include "ViewModelsFactory.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/UI/Base/View.h"

void UViewsFactory::Inject(TObjectPtr<UInstallerContainer> Container)
{
	Super::Inject(Container);
	
	ViewModelsFactory = Container->Resolve<UViewModelsFactory>();
}

void UViewsFactory::InitializeView(UUserWidget* Widget)
{
	if (auto View = Cast<IView>(Widget))
	{
		View->BuildViewModel(ViewModelsFactory);
	}
}
