// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InstallerState.h"
#include "VeilOfFaith/Installer/Initializable.h"
#include "VeilOfFaith/Services/Base/Fragmentable.h"
#include "VeilOfFaith/Services/Base/Tickable.h"
#include "SystemsState.generated.h"

class UFragmentsFactory;
class UInstallerContainer;
class IFragmentable;
class IWorldable;
class IInjectable;

UCLASS()
class VEILOFFAITH_API USystemsState : public UInstallerState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> Container;

	TObjectPtr<UTickService> TickService;
	
	TArray<IInjectable*> Injectables;
	TArray<IInitializable*> Initializables;
	TArray<ITickable*> Tickables;
	TArray<IWorldable*> WorldSettables;
	TArray<IFragmentable*> Modulables;
};
