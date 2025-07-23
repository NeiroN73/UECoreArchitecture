// Copyright Floruit, Inc. All Rights Reserved.


#include "BoardHandler.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/Character.h"
#include "ProjectCoreRuntime/Characters/PlayerHandler.h"
#include "ProjectCoreRuntime/Configs/InputConfig.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Factories/ScreensFactory.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/UI/Board/BoardScreen.h"


ABoardHandler::ABoardHandler()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetStaticMesh(StaticMesh);
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(StaticMeshComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(StaticMeshComponent);

	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionComponent"));
	WidgetInteractionComponent->SetupAttachment(CameraComponent);
	WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::Mouse;
	WidgetInteractionComponent->bEnableHitTesting = true;
}

void ABoardHandler::Inject(TObjectPtr<UInstallerContainer> Container)
{
	InputConfig = Container->Resolve<UInputConfig>();
	ViewFactory = Container->Resolve<UScreensFactory>();
}

void ABoardHandler::Initialize()
{
	if (WidgetComponent)
	{
		auto View = ViewFactory->Create<UBoardScreen>();
		WidgetComponent->SetWidget(View);
	}
}

void ABoardHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	EnableInput(GetWorld()->GetFirstPlayerController());
	if (auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InputConfig->LeftClickAction,
			ETriggerEvent::Triggered, this, &ABoardHandler::OnLeftMousePressed);
		EnhancedInputComponent->BindAction(InputConfig->EscapeAction,
			ETriggerEvent::Triggered, this, &ABoardHandler::Unpossess);
	}
}

bool ABoardHandler::TryInteract(TSharedPtr<FInteractParams> Params)
{
	Params->Pawn = this;
	InvokerCharacter = Params->Invoker;
	
	if (GEditor)
	{
		GEditor->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Interact with board"));
	}

	return true;
}

void ABoardHandler::OnLeftMousePressed()
{
	if (WidgetInteractionComponent)
	{
		WidgetInteractionComponent->PressAndReleaseKey(EKeys::LeftMouseButton);
	}
}

void ABoardHandler::Unpossess()
{
	if (auto Player = Cast<APlayerHandler>(InvokerCharacter))
	{
		Player->Unpossess(InvokerCharacter);
	}
}

void ABoardHandler::AddCard()
{
	// auto Card = HandlerFactory->SpawnHandler<ABoardCardHandler>();
	// if (Card && !Cards.Contains(Card))
	// {
	// 	Cards.Add(Card);
	// }
}

void ABoardHandler::RemoveCard(ABoardCardHandler* Card)
{
}
