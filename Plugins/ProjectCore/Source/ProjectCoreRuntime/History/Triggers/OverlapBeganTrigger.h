// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/HistoryTrigger.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "OverlapBeganTrigger.generated.h"

class UHandlersService;

UCLASS()
class PROJECTCORERUNTIME_API UOverlapBeganTrigger : public UHistoryTrigger
{
	GENERATED_BODY()

public:
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void Bind() override;

	UPROPERTY()
	TObjectPtr<UHandlersService> HandlersService;

	UPROPERTY(EditAnywhere)
	FCustomId InvokerId;
	
	UPROPERTY(EditAnywhere)
	FCustomId OverlapId;
};
