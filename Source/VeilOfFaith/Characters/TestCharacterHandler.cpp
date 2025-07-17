// Copyright Floruit, Inc. All Rights Reserved.


#include "TestCharacterHandler.h"

#include "VeilOfFaith/Fragments/DialogueFragment.h"
#include "VeilOfFaith/Fragments/InteractFragment.h"


bool ATestCharacterHandler::TryInteract(TSharedPtr<FInteractParams> Params)
{
	Params->Character = this;
	
	if (auto Fragment = GetFragment<UDialogueFragment>())
	{
		Fragment->StartDialogue();
		return true;
	}
	return false;
}

void ATestCharacterHandler::Inject(TObjectPtr<UInstallerContainer> Container)
{
	
}

void ATestCharacterHandler::BuildFragments(UFragmentsFactory* NewModuleFactory)
{
	Super::BuildFragments(NewModuleFactory);
}
