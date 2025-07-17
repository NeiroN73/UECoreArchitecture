// Copyright Floruit, Inc. All Rights Reserved.


#include "GravityFragment.h"

UGravityFragment* UGravityFragment::Initialize(float NewGravityForce)
{
	GravityForce = NewGravityForce;
	
	return this;
}

void UGravityFragment::Tick(float DeltaSeconds)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Сила тяжести: %f"), GravityForce));
	}
}
