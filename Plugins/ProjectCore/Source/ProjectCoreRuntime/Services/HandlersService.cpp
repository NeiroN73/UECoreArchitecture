// Copyright Floruit, Inc. All Rights Reserved.


#include "HandlersService.h"

#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Handlers/CharacterHandler.h"
#include "ProjectCoreRuntime/Handlers/Base/ActorHandler.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"

void UHandlersService::Inject(TObjectPtr<UInstallerContainer> Container)
{
	HandlerFactory = Container->Resolve<UHandlersFactory>();
	HandlerFactory->OnCharacterHandlerAdded.BindLambda([this](ACharacterHandler* CharacterHandler)
	{
		AddCharacterHandler(CharacterHandler);
	});
	HandlerFactory->OnActorHandlerAdded.BindLambda([this](AActorHandler* CharacterHandler)
	{
		AddActorHandler(CharacterHandler);
	});
}

void UHandlersService::WorldChanged(UWorld* NewWorld)
{
	Super::WorldChanged(NewWorld);

	CharactersById.Empty();
	HandlersById.Empty();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (auto Character = Cast<ACharacterHandler>(Actor))
		{
			HandlerFactory->InitializeCharacterHandler(Character);
		}
		else if (Actor->Implements<UHandlerable>())
		{
			HandlerFactory->InitializeHandler(Actor);
		}
	}
}

void UHandlersService::AddCharacterHandler(ACharacterHandler* CharacterHandler)
{
	CharactersById.Add(CharacterHandler->Id, CharacterHandler);
}

void UHandlersService::AddActorHandler(AActorHandler* Handler)
{
	HandlersById.Add(Handler->Id, Handler);
}
