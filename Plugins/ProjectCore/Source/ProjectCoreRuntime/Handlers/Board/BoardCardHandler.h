// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/Handlers/Base/Handlerable.h"
#include "BoardCardHandler.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API ABoardCardHandler : public AActorHandler
{
	GENERATED_BODY()

public:
	ABoardCardHandler();
};
