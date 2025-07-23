// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "HandlersService.generated.h"

class ACharacterHandler;
class UHandlersFactory;

UCLASS()
class PROJECTCORERUNTIME_API UHandlersService : public UService,
public IInjectable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<FName, ACharacterHandler*> CharactersById;
	UPROPERTY()
	TMap<FName, AActorHandler*> HandlersById;
	
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	virtual void WorldChanged(UWorld* NewWorld) override;

	template<typename TCharacterHandler = ACharacterHandler>
	TCharacterHandler* GetCharacterHandler(FName Id)
	{
		if (auto Character = CharactersById.FindRef(Id))
		{
			return Cast<TCharacterHandler>(Character);
		}

		return nullptr;
	}
	
	template<typename THandler = AActorHandler>
	THandler* GetActorHandler(FName Id)
	{
		if (auto Actor = HandlersById.FindRef(Id))
		{
			return Cast<THandler>(Actor);
		}

		return nullptr;
	}

private:
	void AddCharacterHandler(ACharacterHandler* CharacterHandler);
	void AddActorHandler(AActorHandler* Handler);

	UPROPERTY()
	TObjectPtr<UHandlersFactory> HandlerFactory;
};
