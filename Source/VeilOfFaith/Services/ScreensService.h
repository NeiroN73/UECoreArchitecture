// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "Components/SlateWrapperTypes.h"
#include "VeilOfFaith/Factories/ScreensFactory.h"
#include "VeilOfFaith/UI/Base/Screen.h"
#include "ScreensService.generated.h"

class UScreensFactory;

UCLASS()
class VEILOFFAITH_API UScreensService : public UService,
public IInjectable
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UScreensFactory> ViewFactory;

	UPROPERTY()
	TMap<TSubclassOf<UScreen>, TObjectPtr<UScreen>> ScreensByClass;

	UPROPERTY()
	TArray<TObjectPtr<UScreen>> ScreensStack;

public:
	UPROPERTY()
	TObjectPtr<UScreen> CurrentScreen;
	
	void Close();
	
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	
	template<class TScreen = UScreen>
	void Open(TSubclassOf<UScreen> InClass = TScreen::StaticClass())
	{
		if (auto FoundScreen = ScreensByClass.FindRef(InClass))
		{
			if (auto CastScreen = Cast<TScreen>(FoundScreen))
			{
				CurrentScreen = CastScreen;
			}
		}
		else
		{
			CurrentScreen = ViewFactory->CreateToViewport<TScreen>();
			if (CurrentScreen)
			{
				ScreensByClass.Add(InClass, CurrentScreen);
			}
		}

		CurrentScreen->SetVisibility(ESlateVisibility::Visible);
		//Screen->Open();
	
		ScreensStack.Push(CurrentScreen);
	}
};
