// Copyright Floruit, Inc. All Rights Reserved.


#include "DialogueFragment.h"

#include "VeilOfFaith/Characters/Base/CharacterHandler.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Services/DialoguesService.h"

void UDialogueFragment::StartDialogue()
{
    DialogueService->StartDialogue(Cast<ACharacterHandler>(Character));
}

void UDialogueFragment::Inject(TObjectPtr<UInstallerContainer> Container)
{
    DialogueService = Container->Resolve<UDialoguesService>();
}
