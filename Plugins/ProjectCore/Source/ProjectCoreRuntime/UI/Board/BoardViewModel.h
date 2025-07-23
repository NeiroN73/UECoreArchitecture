// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/Installer/Initializable.h"
#include "ProjectCoreRuntime/UI/Base/MvvmMacros.h"
#include "ProjectCoreRuntime/UI/Base/ViewModel.h"
#include "ProjectCoreRuntime/UI/Binders/ButtonBinder.h"
#include "BoardViewModel.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UBoardViewModel : public UViewModel,
public IInitializable
{
	GENERATED_BODY()

public:
	//BIND_TO_VIEW_MODEL(MyButton, UButtonBinder)
	
	virtual void Initialize() override;
	void Bind();
};
