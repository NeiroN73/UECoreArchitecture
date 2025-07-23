// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseHistoryElement.generated.h"

class UReturnHistoryElement;
class UHistoryElement;

UENUM()
enum class EElementState : uint8
{
	Locked,
	Completed,
	Skipped
};

UCLASS()
class PROJECTCORERUNTIME_API UBaseHistoryElement : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	EElementState State = EElementState::Locked;
	UPROPERTY(VisibleAnywhere)
	FGuid Guid;
	UPROPERTY(VisibleAnywhere)
	int32 LayerIndex;
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UHistoryElement>> ChildElements;
	UPROPERTY()
	TObjectPtr<UReturnHistoryElement> ReturnElement;

#if WITH_EDITOR
	virtual void PostLoad() override
	{
		Super::PostLoad();

		if (!Guid.IsValid())
		{
			Guid = FGuid::NewGuid();
		}
	}

	virtual void PostInitProperties() override
	{
		Super::PostInitProperties();

		if (!Guid.IsValid())
		{
			Guid = FGuid::NewGuid();
		}
	}
#endif
};
