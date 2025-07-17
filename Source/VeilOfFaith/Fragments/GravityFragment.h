// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Fragment.h"
#include "VeilOfFaith/Services/Base/Tickable.h"
#include "GravityFragment.generated.h"

UCLASS()
class VEILOFFAITH_API UGravityFragment : public UFragment,
public ITickable
{
	GENERATED_BODY()

public:
	UGravityFragment* Initialize(float NewGravityForce);
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY()
	float GravityForce;
};
