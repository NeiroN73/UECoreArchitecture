// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HandlersFactory.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/Handlers/Base/ObjectPoolHandler.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "HandlerObjectPool.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UHandlerObjectPool : public UObject,
public IInjectable
{
	GENERATED_BODY()

public:
	template<typename THandler = AObjectPoolHandler>
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

	template<typename THandler = AObjectPoolHandler>
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

	void Return(AObjectPoolHandler* Handler);
	void Release();
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;

private:
	UPROPERTY()
	TArray<TObjectPtr<AObjectPoolHandler>> Pool;

	UPROPERTY()
	TObjectPtr<UHandlersFactory> HandlerFactory;

	UPROPERTY()
	TObjectPtr<AActor> PoolContainer;

	UPROPERTY()
	TSubclassOf<AObjectPoolHandler> Class;
};
