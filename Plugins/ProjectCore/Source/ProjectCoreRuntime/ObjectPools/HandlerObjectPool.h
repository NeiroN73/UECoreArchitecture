// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseObjectPool.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/Handlers/Base/PoolableHandler.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "HandlerObjectPool.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UHandlerObjectPool : public UBaseObjectPool,
public IInjectable
{
	GENERATED_BODY()

public:
	template<typename THandler = APoolableHandler>
	void Create(AActor* PoolsContainer, int32 Size)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = FName("PoolContainer");
		PoolContainer = GetWorld()->SpawnActor<AActor>(SpawnParams);
		USceneComponent* PoolSceneComponent = NewObject<USceneComponent>(PoolContainer);
		PoolContainer->SetRootComponent(PoolSceneComponent);
		PoolContainer->AttachToActor(PoolsContainer, FAttachmentTransformRules::KeepWorldTransform);
		Class = THandler::StaticClass();
		
		for (int32 i = 0; i < Size; i++)
		{
			Get<THandler>();
		}
	}

	template<typename THandler = APoolableHandler>
	TObjectPtr<THandler> Get()
	{
		for (auto Handler : Pool)
		{
			if (Handler && Handler->IsHidden())
			{
				Handler->Get();
				return Cast<THandler>(Handler);
			}
		}
		auto NewHandler = HandlerFactory->SpawnHandler<THandler>();
		NewHandler->Get();
		Pool.Add(NewHandler);
		NewHandler->AttachToActor(PoolContainer, FAttachmentTransformRules::KeepWorldTransform);
		return NewHandler;
	}

	void Return(APoolableHandler* Handler);
	void Release();
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;

private:
	UPROPERTY()
	TArray<TObjectPtr<APoolableHandler>> Pool;

	UPROPERTY()
	TObjectPtr<UHandlersFactory> HandlerFactory;

	UPROPERTY()
	TObjectPtr<AActor> PoolContainer;

	UPROPERTY()
	TSubclassOf<APoolableHandler> Class;
};
