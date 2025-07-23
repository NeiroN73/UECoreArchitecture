// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "ProjectCoreRuntime/Installer/Initializable.h"
#include "HandlersConfig.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UHandlersConfig : public UConfig
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<FCustomId, TSubclassOf<AActor>> HandlersById;
};
