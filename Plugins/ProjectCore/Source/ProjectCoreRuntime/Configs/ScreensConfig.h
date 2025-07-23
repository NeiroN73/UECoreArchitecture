// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "Engine/DataAsset.h"
#include "ProjectCoreRuntime/UI/Base/Screen.h"
#include "ScreensConfig.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UScreensConfig : public UConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSet<TSubclassOf<UScreen>> Screens;

	template<typename TScreen = UScreen>
	UClass* GetScreenClass()
	{
		auto Class = TScreen::StaticClass();
		for (auto ViewClass : Screens)
		{
			if (ViewClass->IsChildOf(Class))
			{
				return ViewClass.Get();
			}
		}
    
		return nullptr;
	}
};
