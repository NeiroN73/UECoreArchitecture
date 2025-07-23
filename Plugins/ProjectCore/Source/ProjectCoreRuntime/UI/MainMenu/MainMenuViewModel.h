// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Installer/Initializable.h"
#include "ProjectCoreRuntime/Services/LevelsService.h"
#include "ProjectCoreRuntime/UI/Base/MvvmMacros.h"
#include "ProjectCoreRuntime/UI/Base/ViewModel.h"
#include "ProjectCoreRuntime/UI/Binders/ButtonBinder.h"
#include "MainMenuViewModel.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UMainMenuViewModel : public UViewModel,
public IInjectable
{
	GENERATED_BODY()

	//BIND_TO_VIEW_MODEL(ContinueButton, UButtonBinder)

public:
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	void Bind();
	
private:
	UPROPERTY()
	TObjectPtr<ULevelsService> LevelsService;
};
