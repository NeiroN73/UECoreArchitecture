// Copyright Floruit, Inc. All Rights Reserved.


#include "SetDialogueAction.h"

#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Services/DialoguesService.h"

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
