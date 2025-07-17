// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VeilOfFaith/Installer/Initializable.h"
#include "VeilOfFaith/Services/LevelsService.h"
#include "VeilOfFaith/UI/Base/MvvmMacros.h"
#include "VeilOfFaith/UI/Base/ViewModel.h"
#include "VeilOfFaith/UI/Binders/ButtonBinder.h"
#include "MainMenuViewModel.generated.h"

UCLASS()
class VEILOFFAITH_API UMainMenuViewModel : public UViewModel,
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
