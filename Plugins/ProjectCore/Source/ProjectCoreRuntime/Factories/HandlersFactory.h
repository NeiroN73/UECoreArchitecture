// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/Services/HandlersService.h"
#include "ProjectCoreRuntime/TableConfigs/CharactersTableData.h"
#include "HandlersFactory.generated.h"

class UHandlersConfig;
class AGameplayGameMode;

DECLARE_DELEGATE_OneParam(FOnCharacterHandlerAdded, ACharacterHandler*)
DECLARE_DELEGATE_OneParam(FOnActorHandlerAdded, AActorHandler*)

UCLASS()
class PROJECTCORERUNTIME_API UHandlersFactory : public UBaseFactory
{
	GENERATED_BODY()

public:
	FOnCharacterHandlerAdded OnCharacterHandlerAdded;
	FOnActorHandlerAdded OnActorHandlerAdded;
	
	template<class TActor = AActor>
	TActor* SpawnHandler(FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator,
		TSubclassOf<AActor> Class = TActor::StaticClass())
	{
		if (auto Handler = World->SpawnActor<TActor>(Class, Location, Rotation))
		{
			InitializeHandler(Handler);
			return Handler;
		}
		
		return nullptr;
	}

	template<class TCharacter = ACharacterHandler>
	TCharacter* SpawnCharacterHandler(FName Id, FVector Location = FVector::ZeroVector,
		FRotator Rotation = FRotator::ZeroRotator)
	{
		auto Data = CharactersTableConfig->FindRow<FCharactersTableData>(Id, "");
		auto Handler = SpawnHandler<TCharacter>(Location, Rotation, Data->Class);
		InitializeCharacterHandler(Handler);

		if (auto PlayerController = UGameplayStatics::GetPlayerController(World, 0))
		{
			PlayerController->Possess(Handler);
		}

		return Handler;
	}

	void InitializeCharacterHandler(ACharacterHandler* Handler);
	void InitializeHandler(AActor* Actor);

	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> CharactersTableConfig;
};