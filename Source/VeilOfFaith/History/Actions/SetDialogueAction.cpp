// Copyright Floruit, Inc. All Rights Reserved.


#include "SetDialogueAction.h"

#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Services/DialoguesService.h"

void USetDialogueAction::Inject(UInstallerContainer* Container)
{
	DialoguesService = Container->Resolve<UDialoguesService>();
}

void USetDialogueAction::Execute()
{
	DialoguesService->SetDialogue(CharacterId, DialogueId);
}

TArray<FName> USetDialogueAction::GetPreloadIds()
{
	return { DialogueId };
}
