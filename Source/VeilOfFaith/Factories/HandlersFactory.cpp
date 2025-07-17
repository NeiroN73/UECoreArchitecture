// Copyright Floruit, Inc. All Rights Reserved.


#include "HandlersFactory.h"

#include "VeilOfFaith/Characters/Base/CharacterHandler.h"
#include "VeilOfFaith/Handlers/Base/ActorHandler.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/TableConfigs/CharactersTableData.h"

void UHandlersFactory::InitializeCharacterHandler(ACharacterHandler* Handler)
{
	auto Data = CharactersTableConfig->FindRow<FCharactersTableData>(Handler->Id, "");
	Handler->Data = Data;
	InitializeHandler(Handler);

	OnCharacterHandlerAdded.ExecuteIfBound(Handler);
}

void UHandlersFactory::InitializeHandler(AActor* Actor)
{
	CastInterfaces(Actor);

	if (auto Handler = Cast<AActorHandler>(Actor))
	{
		OnActorHandlerAdded.ExecuteIfBound(Handler);
	}
}

void UHandlersFactory::Inject(TObjectPtr<UInstallerContainer> Container)
{
	Super::Inject(Container);
	
	CharactersTableConfig = Container->ResolveTableConfig<FCharactersTableData>();
}
