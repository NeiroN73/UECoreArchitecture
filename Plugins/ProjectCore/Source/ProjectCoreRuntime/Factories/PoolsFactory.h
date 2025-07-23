// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "ProjectCoreRuntime/ObjectPools/Base/BaseObjectPool.h"
#include "UObject/Object.h"
#include "PoolsFactory.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UPoolsFactory : public UBaseFactory
{
	GENERATED_BODY()

public:
	template<typename TObjectPool = UBaseObjectPool>
	TObjectPool* Create(int32 Size = 0)
	{
		if (!PoolsContainer)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Name = FName("PoolsContainer");
			PoolsContainer = World->SpawnActor<AActor>(SpawnParams);
			PoolsContainer->Rename(TEXT("PoolsContainer"));
			auto PoolSceneComponent = NewObject<USceneComponent>(PoolsContainer);
			PoolsContainer->SetRootComponent(PoolSceneComponent);
		}

		auto Pool = NewObject<TObjectPool>(World);
		CastInterfaces(Pool);
		//Pool->Create(PoolsContainer, Size);
		return Pool;
	}

private:
	UPROPERTY()
	TObjectPtr<AActor> PoolsContainer;
};
