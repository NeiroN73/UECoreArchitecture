// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HistoryAction.generated.h"

class UInstallerContainer;
class UHistoryService;

UCLASS(Blueprintable, BlueprintType, Abstract, EditInlineNew)
class PROJECTCORERUNTIME_API UHistoryAction : public UObject
{
	GENERATED_BODY()

public:
	virtual void Inject(UInstallerContainer* Container) {}
	virtual void Execute() {}
};
