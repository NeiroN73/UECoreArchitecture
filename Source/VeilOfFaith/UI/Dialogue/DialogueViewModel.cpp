// Copyright Floruit, Inc. All Rights Reserved.


#include "DialogueViewModel.h"

#include "DialogueOptionView.h"
#include "DialogueOptionViewModel.h"
#include "Components/PanelWidget.h"
#include "DlgSystem/DlgContext.h"
#include "VeilOfFaith/Factories/ViewsFactory.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Services/DialoguesService.h"


void UDialogueViewModel::Bind(UPanelWidget* InOptionsContainer, TSubclassOf<UDialogueOptionView> InOptionClass)
{
	OptionsContainer = InOptionsContainer;
	OptionClass = InOptionClass;
	
	DialoguesService->DialogueProgressed.BindUObject(this, &UDialogueViewModel::UpdateData);

	UpdateData();
}

void UDialogueViewModel::Inject(TObjectPtr<UInstallerContainer> Container)
{
	DialoguesService = Container->Resolve<UDialoguesService>();
	ViewsFactory = Container->Resolve<UViewsFactory>();
}

void UDialogueViewModel::UpdateData()
{
	auto DlgContext = DialoguesService->GetCurrentContext();
	SetCharacterName(DlgContext->GetActiveNodeParticipantName());
	SetPhraseText(DlgContext->GetActiveNodeText());

	//todo: переделать потом через пул
	for (auto OptionView : OptionViews)
	{
		OptionView->RemoveFromParent();
	}
	OptionViews.Empty();
	
	const auto& OptionEdges = DlgContext->GetOptionsArray();
	for (int32 It = 0; It < OptionEdges.Num(); ++It)
	{
		auto View = ViewsFactory->Create<UDialogueOptionView>(OptionClass);
		View->ViewModel->OptionIndex = It;
		View->ViewModel->Bind();
		
		OptionsContainer->AddChild(View);
		OptionViews.Add(View);
	}
}
