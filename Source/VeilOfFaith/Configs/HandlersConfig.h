// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "VeilOfFaith/EditorUtils/CustomId.h"
#include "VeilOfFaith/Installer/Initializable.h"
#include "HandlersConfig.generated.h"

UCLASS()
class VEILOFFAITH_API UHandlersConfig : public UConfig,
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
