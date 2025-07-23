// Copyright Floruit, Inc. All Rights Reserved.


#include "DialogueFragment.h"

#include "ProjectCoreRuntime/Characters/Base/CharacterHandler.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Services/DialoguesService.h"

void UDialogueFragment::StartDialogue()
{
    DialogueService->StartDialogue(Cast<ACharacterHandler>(Character));
}

void UDialogueFragment::Inject(TObjectPtr<UInstallerContainer> Container)
{
    DialogueService = Container->Resolve<UDialoguesService>();
}
