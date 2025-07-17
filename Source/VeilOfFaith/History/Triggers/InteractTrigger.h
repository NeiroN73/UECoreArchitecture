// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/HistoryTrigger.h"
#include "VeilOfFaith/EditorUtils/CustomId.h"
#include "InteractTrigger.generated.h"

class UHandlersService;

UCLASS()
class VEILOFFAITH_API UInteractTrigger : public UHistoryTrigger
{
	GENERATED_BODY()

public:
	virtual void Inject(UInstallerContainer* Container) override;
	virtual void Bind() override;

	UPROPERTY()
	TObjectPtr<UHandlersService> HandlersService;

	UPROPERTY(EditAnywhere)
	FCustomId InvokerCharacterId;
	
	UPROPERTY(EditAnywhere)
	FCustomId TargetHandlerId;
};
