// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/ActorHandler.h"
#include "TriggerHandler.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnOverlapBegan, AActor* OtherActor);

UCLASS()
class PROJECTCORERUNTIME_API ATriggerHandler : public AActorHandler
{
	GENERATED_BODY()

public:
	ATriggerHandler();

	FOnOverlapBegan OnOverlapBegan;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
