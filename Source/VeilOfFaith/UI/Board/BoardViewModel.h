// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VeilOfFaith/Installer/Initializable.h"
#include "VeilOfFaith/UI/Base/MvvmMacros.h"
#include "VeilOfFaith/UI/Base/ViewModel.h"
#include "VeilOfFaith/UI/Binders/ButtonBinder.h"
#include "BoardViewModel.generated.h"

UCLASS()
class VEILOFFAITH_API UBoardViewModel : public UViewModel,
public IInitializable
{
	GENERATED_BODY()

public:
	//BIND_TO_VIEW_MODEL(MyButton, UButtonBinder)
	
	virtual void Initialize() override;
	void Bind();
};
