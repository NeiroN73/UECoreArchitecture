// Copyright Floruit, Inc. All Rights Reserved.


#include "InteractTrigger.h"

#include "ProjectCoreRuntime/Characters/Base/CharacterHandler.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Fragments/InteractFragment.h"
#include "ProjectCoreRuntime/Services/HandlersService.h"

void UInteractTrigger::Inject(UInstallerContainer* Container)
{
	HandlersService = Container->Resolve<UHandlersService>();
}

void UInteractTrigger::Bind()
{
	if (auto Handler = HandlersService->GetCharacterHandler(InvokerCharacterId))
	{
		if (auto Module = Handler->GetFragment<UInteractFragment>())
		{
			Module->OnInteracted.AddLambda([this](FName TargetId)
			{
				if (TargetId.IsEqual(TargetHandlerId))
				{
					MarkTriggered();
				}
			});
		}
	}
}
