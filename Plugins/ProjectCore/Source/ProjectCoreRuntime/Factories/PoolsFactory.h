// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HandlerObjectPool.h"
#include "Base/BaseFactory.h"
#include "UObject/Object.h"
#include "PoolsFactory.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UPoolsFactory : public UBaseFactory
{
	GENERATED_BODY()

public:
	template<typename THandler = AHandler>
	UHandlerObjectPool* Create(int32 Size = 0)
	{
		if (!PoolsContainer)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Name = FName("PoolsContainer");
			PoolsContainer = World->SpawnActor<AActor>(SpawnParams);
			PoolsContainer->Rename(TEXT("PoolsContainer"));
			USceneComponent* PoolSceneComponent = NewObject<USceneComponent>(PoolsContainer);
			PoolsContainer->SetRootComponent(PoolSceneComponent);
		}

		auto Pool = NewObject<UHandlerObjectPool>(World);
		CastInterfaces(Pool);
		Pool->Create<THandler>(PoolsContainer, Size);
		return Pool;
	}

private:
	UPROPERTY()
	TObjectPtr<AActor> PoolsContainer;
};
