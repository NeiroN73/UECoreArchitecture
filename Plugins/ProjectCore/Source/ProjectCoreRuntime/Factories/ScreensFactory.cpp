// Copyright Floruit, Inc. All Rights Reserved.


#include "ScreensFactory.h"

#include "ViewModelsFactory.h"

void UScreensFactory::Inject(TObjectPtr<UInstallerContainer> Container)
{
	Super::Inject(Container);

	ViewModelFactory = Container->Resolve<UViewModelsFactory>();
	ScreensConfig = Container->Resolve<UScreensConfig>();
	AssetsLoaderService = Container->Resolve<UAssetsService>();
}

void UScreensFactory::InitializeView(UUserWidget* Widget)
{
	if (auto View = Cast<IView>(Widget))
	{
		View->BuildViewModel(ViewModelFactory);
	}
}
