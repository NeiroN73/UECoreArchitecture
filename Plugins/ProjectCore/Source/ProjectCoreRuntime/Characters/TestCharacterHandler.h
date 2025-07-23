// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/CharacterHandler.h"
#include "ProjectCoreRuntime/Handlers/Base/Interactable.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "ProjectCoreRuntime/Services/Base/Fragmentable.h"
#include "TestCharacterHandler.generated.h"

class UFragmentsFactory;

UCLASS()
class PROJECTCORERUNTIME_API ATestCharacterHandler : public ACharacterHandler,
public IInjectable,
public IInteractable
{
	GENERATED_BODY()
	
public:
	virtual bool TryInteract(TSharedPtr<FInteractParams> Params = MakeShared<FInteractParams>()) override;
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	virtual void BuildFragments(UFragmentsFactory* NewModuleFactory) override;
};
