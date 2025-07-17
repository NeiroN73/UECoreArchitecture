// Copyright Floruit, Inc. All Rights Reserved.


#include "OverlapBeganTrigger.h"

#include "VeilOfFaith/Handlers/TriggerHandler.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Services/HandlersService.h"

void UOverlapBeganTrigger::Inject(UInstallerContainer* Container)
{
	HandlersService = Container->Resolve<UHandlersService>();
}

void UOverlapBeganTrigger::Bind()
{
	if (auto Handler = HandlersService->GetActorHandler<ATriggerHandler>(OverlapId))
	{
		Handler->OnOverlapBegan.AddLambda([this](AActor* OtherActor)
		{
			if (auto OtherHandler = Cast<IHandlerable>(OtherActor))
			{
				if (InvokerId == OtherHandler->GetId())
				{
					MarkTriggered();
				}
			}
		});
	}
}