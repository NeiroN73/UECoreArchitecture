// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "ProjectCoreRuntime/Installer/Worldable.h"
#include "BaseFactory.generated.h"

class UTickService;
class UFragmentsFactory;
class UInstallerContainer;

UCLASS()
class PROJECTCORERUNTIME_API UBaseFactory : public UObject,
public IInjectable,
public IWorldable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UWorld> World;
	
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	virtual void WorldChanged(UWorld* NewWorld) override;

protected:
	void CastInterfaces(UObject* Object);
	void CastInjectable(UObject* Object);
	void CastInitializable(UObject* Object);
	void CastTickable(UObject* Object);
	void CastFragmentable(UObject* Object);

private:
	UPROPERTY()
	TObjectPtr<UInstallerContainer> InstallerContainer;
	UPROPERTY()
	TObjectPtr<UTickService> TickService;
	UPROPERTY()
	TObjectPtr<UFragmentsFactory> FragmentsFactory;
};
