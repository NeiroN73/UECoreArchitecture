// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/InstallerState.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "InitializeSystemsState.generated.h"

class UTickService;
class IInitializable;
class IInjectable;
class ITickable;
class IFragmentable;

UCLASS()
class PROJECTCORERUNTIME_API UInitializeSystemsState : public UInstallerState
{
	GENERATED_BODY()
	
public:
	virtual void Enter() override;

private:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> Container;

	TArray<IInjectable*> Injectables;
	TArray<IInitializable*> Initializables;
	TArray<ITickable*> Tickables;
	TArray<IFragmentable*> Fragmentables;
	
	void RegisterConfigs();
	void RegisterSaveStates();
	void RegisterTableConfigs();
	void RegisterServices();
	void RegisterFactories();
	void InitializeSystems();
	
	void Register(UObject* Object);
	
	template<typename T>
	void Register()
	{
		StateMachine->InstallerContainer->Register<T>();
	}
};