// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "ProjectCoreRuntime/Installer/Initializable.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "InvestigationService.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UInvestigationService : public UService,
public IInjectable,
public IInitializable
{
	GENERATED_BODY()

public:
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	virtual void Initialize() override;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> DaysTableConfig;
};
