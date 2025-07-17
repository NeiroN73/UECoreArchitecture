// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HistoryTrigger.generated.h"

class UInstallerContainer;

DECLARE_DELEGATE(FOnTriggered)

UCLASS(Blueprintable, BlueprintType, Abstract, EditInlineNew)
class VEILOFFAITH_API UHistoryTrigger : public UObject
{
	GENERATED_BODY()

public:
	FOnTriggered OnTriggered;
	bool bTriggered;
	
	virtual void Inject(UInstallerContainer* Container) PURE_VIRTUAL(UHistoryTrigger::Inject)
	virtual void Bind() PURE_VIRTUAL(UHistoryTrigger::Trigger)

	void MarkTriggered();
};
