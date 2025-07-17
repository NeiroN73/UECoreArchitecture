// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VeilOfFaith/Installer/Injectable.h"
#include "VeilOfFaith/Installer/Worldable.h"
#include "BaseFactory.generated.h"

class UTickService;
class UFragmentsFactory;
class UInstallerContainer;

UCLASS()
class VEILOFFAITH_API UBaseFactory : public UObject,
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
	TObjectPtr<UInstallerContainer> InstallerContainer;
	TObjectPtr<UTickService> TickService;
	TObjectPtr<UFragmentsFactory> FragmentsFactory;

	void CastInterfaces(UObject* Object);

	void CastInjectable(UObject* Object);
	void CastInitializable(UObject* Object);
	void CastTickable(UObject* Object);
	void CastModulable(UObject* Object);
};
