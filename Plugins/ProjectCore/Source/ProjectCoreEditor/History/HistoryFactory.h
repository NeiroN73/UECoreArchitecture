// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "HistoryFactory.generated.h"

UCLASS()
class PROJECTCOREEDITOR_API UHistoryFactory : public UFactory
{
	GENERATED_BODY()

public:
	UHistoryFactory(const FObjectInitializer& ObjectInitializer);

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
		EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
