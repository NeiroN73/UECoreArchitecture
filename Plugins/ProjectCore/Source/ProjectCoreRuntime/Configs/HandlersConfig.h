// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "ProjectCoreRuntime/Installer/Initializable.h"
#include "HandlersConfig.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UHandlersConfig : public UConfig,
public IInitializable
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;

	TMap<FCustomId, TSubclassOf<AActor>> HandlersById;

	TSubclassOf<AActor> GetHandlerClass(FName Id)
	{
		if (auto Founded = HandlersById.Find(Id))
		{
			return *Founded;
		}
		return nullptr;
	}

private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> Handlers;
};
