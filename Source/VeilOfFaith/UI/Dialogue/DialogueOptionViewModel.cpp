// Copyright Floruit, Inc. All Rights Reserved.


#include "DialogueOptionViewModel.h"

#include "DlgSystem/DlgContext.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Services/DialoguesService.h"

void UDialogueOptionViewModel::Bind()
{
	BindNextButton(FSimpleDelegate::CreateUObject(this, &UDialogueOptionViewModel::ProgressDialogue));
	
	UpdateData();
}

void UDialogueOptionViewModel::Inject(TObjectPtr<UInstallerContainer> Container)
{
	DialoguesService = Container->Resolve<UDialoguesService>();
}

void UDialogueOptionViewModel::ProgressDialogue()
{
	DialoguesService->ProgressDialogue(OptionIndex);

	UpdateData();
}

void UDialogueOptionViewModel::UpdateData()
{
	if (auto DlgContext = DialoguesService->GetCurrentContext())
	{
		if (DlgContext->IsValidOptionIndex(OptionIndex + 1))
		{
			SetAnswerText(DlgContext->GetOptionText(OptionIndex + 1));
		}
	}
}
