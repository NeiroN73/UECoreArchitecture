// Copyright Floruit, Inc. All Rights Reserved.


#include "InteractTrigger.h"

#include "VeilOfFaith/Characters/Base/CharacterHandler.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Fragments/InteractFragment.h"
#include "VeilOfFaith/Services/HandlersService.h"

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
