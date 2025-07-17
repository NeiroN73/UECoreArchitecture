// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HistoryCondition.generated.h"

class UHistoryConfig;
class UInstallerContainer;
class UHistoryService;

DECLARE_DELEGATE(FOnCompleted)

UCLASS(Blueprintable, BlueprintType, Abstract, EditInlineNew)
class VEILOFFAITH_API UHistoryCondition : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FGuid NextElementId;
	
	FOnCompleted OnCompleted;
	bool bCompleted;
	
	virtual void Inject(UInstallerContainer* Container) {}
	virtual void Check() PURE_VIRTUAL(UHistoryCondition::Check)

	void MarkCompleted();
};
