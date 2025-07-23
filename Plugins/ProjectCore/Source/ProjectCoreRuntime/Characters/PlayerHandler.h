// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/CharacterHandler.h"
#include "ProjectCoreRuntime/Installer/Initializable.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "PlayerHandler.generated.h"

class UHealthAttributeSet;
class UAbilitySystemComponent;
class UDialoguesService;
class UGravityFragment;
class UInstallerGameSubsystem;
class UInputConfig;
class UTabletComponent;
class UInputAction;
class UInputComponent;
class UInputMappingContext;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class PROJECTCORERUNTIME_API APlayerHandler : public ACharacterHandler,
public IInjectable
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartInteract();

	UPROPERTY()
	TObjectPtr<UInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

public:
	APlayerHandler();

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	
	void Possess(APawn* Pawn);
	void Unpossess(ACharacter* Character);

	void SetInputModeGameOnly();
	void SetInputModeGameAndUI();
	void SetInputModeUIOnly();
};
