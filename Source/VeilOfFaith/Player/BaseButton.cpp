// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseButton.h"

#include "Components/BoxComponent.h"


ABaseButton::ABaseButton()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	// BoxCollider->SetBoxExtent(StaticMesh->GetStaticMesh()->GetBounds().BoxExtent);
	// BoxCollider->SetCollisionProfileName(TEXT("Trigger"));

	//BoxCollider->SetupAttachment(StaticMesh);
	//StaticMesh->SetRelativeLocation(FVector(10.0f, 50.0f, 50.0f));
}
