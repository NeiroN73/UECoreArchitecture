// Copyright Floruit, Inc. All Rights Reserved.


#include "TriggerHandler.h"

#include "Components/BoxComponent.h"


ATriggerHandler::ATriggerHandler()
{
	UBoxComponent* TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetGenerateOverlapEvents(true);
	RootComponent = TriggerBox;
}

void ATriggerHandler::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* TriggerComponent = Cast<UPrimitiveComponent>(RootComponent))
	{
		TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ATriggerHandler::OnOverlapBegin);
	}
}

void ATriggerHandler::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnOverlapBegan.Broadcast(OtherActor);
}