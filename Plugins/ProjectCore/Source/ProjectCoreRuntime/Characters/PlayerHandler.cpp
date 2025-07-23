// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHandler.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ProjectCoreRuntime/Configs/InputConfig.h"
#include "ProjectCoreRuntime/Fragments/DialogueFragment.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Fragments/InteractFragment.h"
#include "ProjectCoreRuntime/Handlers/Base/InteractParams.h"
#include "ProjectCoreRuntime/Services/DialoguesService.h"

APlayerHandler::APlayerHandler()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->bUsePawnControlRotation = true;
}

void APlayerHandler::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	
	if (APlayerController* InPlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController = InPlayerController;
		
		if (auto Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(InPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputConfig->PlayerMappingContext, 0);
		}
	}

	// объявляется здесь, потому что здесь получается Controller
	if (Controller)
	{
		if (auto Fragment = TryAddFragment<UInteractFragment>())
		{
			Fragment->Initialize(this, Controller);
		}
		if (auto Fragment = TryAddFragment<UDialogueFragment>())
		{
			Fragment->Initialize(this, Controller);
		}
	}
}

void APlayerHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputConfig->MoveAction,
			ETriggerEvent::Triggered, this, &APlayerHandler::Move);
		EnhancedInputComponent->BindAction(InputConfig->LookAction,
			ETriggerEvent::Triggered, this, &APlayerHandler::Look);
		EnhancedInputComponent->BindAction(InputConfig->InteractAction,
			ETriggerEvent::Triggered, this, &APlayerHandler::StartInteract);
	}
}

void APlayerHandler::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerHandler::Inject(TObjectPtr<UInstallerContainer> Container)
{
	InputConfig = Container->Resolve<UInputConfig>();
	
	auto DialoguesService = Container->Resolve<UDialoguesService>();
	DialoguesService->DialogueFinished.BindUObject(this, &APlayerHandler::SetInputModeGameOnly);
}

void APlayerHandler::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerHandler::StartInteract()
{
	if (auto Fragment = GetFragment<UInteractFragment>())
	{
		auto Params = MakeShared<FInteractParams>();
		
		if (Fragment->TryInteract(Params))
		{
			if (Params->Pawn)
			{
				Possess(Params->Pawn);
			}
			if (Params->Character)
			{
				SetInputModeUIOnly();
			}
		}
	}
}

void APlayerHandler::Possess(APawn* Pawn)
{
	if (PlayerController)
	{
		PlayerController->bAutoManageActiveCameraTarget = false;
		PlayerController->SetViewTargetWithBlend(Pawn,1, VTBlend_Linear, 0.0f, true);
		PlayerController->Possess(Pawn);
		
		SetInputModeGameAndUI();
	}
}

void APlayerHandler::Unpossess(ACharacter* Character)
{
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(Character,1, VTBlend_Linear, 0.0f, true);
		PlayerController->bAutoManageActiveCameraTarget = true;
		PlayerController->Possess(Character);
		
		SetInputModeGameOnly();
	}
}

void APlayerHandler::SetInputModeGameOnly()
{
	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(false);
}

void APlayerHandler::SetInputModeGameAndUI()
{
	FInputModeGameAndUI InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(true);
}

void APlayerHandler::SetInputModeUIOnly()
{
	FInputModeUIOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(true);
}
