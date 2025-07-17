// Copyright Floruit, Inc. All Rights Reserved.


#include "ScreensService.h"

void UScreensService::Close()
{
	if (ScreensStack.Num() > 0)
	{
		auto ViewObject = ScreensStack.Pop();
		ViewObject->SetVisibility(ESlateVisibility::Collapsed);
		
		if (auto View = Cast<UScreen>(ViewObject))
		{
			//View->Close();
		}
	}
}

void UScreensService::Inject(TObjectPtr<UInstallerContainer> Container)
{
	ViewFactory = Container->Resolve<UScreensFactory>();
}
