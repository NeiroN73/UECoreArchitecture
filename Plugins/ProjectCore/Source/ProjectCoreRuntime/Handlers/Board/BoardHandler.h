// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectCoreRuntime/Handlers/Base/Interactable.h"
#include "ProjectCoreRuntime/Handlers/Base/PawnHandler.h"
#include "ProjectCoreRuntime/Installer/Initializable.h"
#include "BoardHandler.generated.h"

class ABoardCardHandler;
class UHandlersFactory;
class UScreensFactory;
class UHandlersConfig;
class UInputConfig;
class UWidgetInteractionComponent;
class UCameraComponent;
class UView;
class UWidgetComponent;

UCLASS()
class PROJECTCORERUNTIME_API ABoardHandler : public APawnHandler,
public IInjectable,
public IInitializable,
public IInteractable
{
	GENERATED_BODY()

public:
	ABoardHandler();

	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	virtual void Initialize() override;
	virtual bool TryInteract(TSharedPtr<FInteractParams> Params = MakeShared<FInteractParams>()) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category = View, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = View, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh> StaticMesh;
	
	UPROPERTY(EditAnywhere, Category = View, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditAnywhere, Category = View, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetInteractionComponent> WidgetInteractionComponent;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY()
	TObjectPtr<UInputConfig> InputConfig;
	UPROPERTY()
	TObjectPtr<UScreensFactory> ViewFactory;
	UPROPERTY()
	TObjectPtr<UHandlersFactory> HandlerFactory;
	
	UPROPERTY()
	TObjectPtr<ACharacter> InvokerCharacter;
	UPROPERTY()
	TArray<ABoardCardHandler*> Cards;

	void OnLeftMousePressed();
	void Unpossess();
	void AddCard();
	void RemoveCard(ABoardCardHandler* Card);
};
