// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseButton.generated.h"

class UBoxComponent;
class APlayerHandler;

DECLARE_DELEGATE(FOnButtonInteracted);

UCLASS()
class VEILOFFAITH_API ABaseButton : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collider, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
public:
	ABaseButton();

	FOnButtonInteracted OnButtonInteracted;
};
