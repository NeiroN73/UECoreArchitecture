// Copyright Floruit, Inc. All Rights Reserved.


#include "DialoguesService.h"

#include "AssetsLoader.h"
#include "HandlersService.h"
#include "PreloadsService.h"
#include "ScreensService.h"
#include "DlgSystem/DlgContext.h"
#include "DlgSystem/DlgManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/DialogueWave.h"
#include "ProjectCoreRuntime/Characters/Base/CharacterHandler.h"
#include "ProjectCoreRuntime/Configs/DialoguesConfig.h"
#include "ProjectCoreRuntime/Fragments/DialogueFragment.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/TableConfigs/CharactersTableData.h"
#include "ProjectCoreRuntime/UI/Dialogue/DialogueScreen.h"

void UDialoguesService::Inject(TObjectPtr<UInstallerContainer> Container)
{
	CharactersTableConfig = Container->ResolveTableConfig<FCharactersTableData>();
	CharactersService = Container->Resolve<UHandlersService>();
	DialoguesConfig = Container->Resolve<UDialoguesConfig>();
	AssetsService = Container->Resolve<UAssetsService>();
	PreloadsService = Container->Resolve<UPreloadsService>();
	ScreensService = Container->Resolve<UScreensService>();
}

void UDialoguesService::StartDialogue(ACharacterHandler* TargetCharacter)
{
	if (auto Fragment = TargetCharacter->GetFragment<UDialogueFragment>())
	{
		auto Dialogue = Fragment->CurrentDialogue;
		auto ParticipantIds = Dialogue->GetParticipantNames();
		TArray<UObject*> Participants;
		for (auto ParticipantId : ParticipantIds)
		{
			if (auto Character = CharactersService->GetCharacterHandler(ParticipantId))
			{
				Participants.Add(Character);
			}
		}
	
		CurrentContext = UDlgManager::StartDialogue(Dialogue, Participants);
		ScreensService->Open<UDialogueScreen>();

		auto DialogueWave = CurrentContext->GetActiveNodeVoiceDialogueWave();
		FDialogueContext DialogueContext = DialogueWave->ContextMappings[0].Context;

		UGameplayStatics::SpawnDialogueAttached(DialogueWave, DialogueContext, TargetCharacter->GetRootComponent());
	
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow,
				FString::Printf(TEXT("Dialogue started: %s"), *Dialogue->GetName()));
		}
	}
}

void UDialoguesService::SetDialogue(FName CharacterId, FName DialogueId)
{
	auto Character = CharactersService->GetCharacterHandler(CharacterId);
	if (auto Fragment = Character->TryAddFragment<UDialogueFragment>())
	{
		Fragment->Initialize(Character, Character->Controller);
		Fragment->CurrentDialogue = PreloadsService->GetLoadedAsset<UDlgDialogue>(DialogueId);
	}
}

void UDialoguesService::ProgressDialogue(int32 OptionIndex)
{
	if (!CurrentContext || !CurrentContext->IsValidOptionIndex(OptionIndex))
	{
		return;
	}

	if (!CurrentContext->ChooseOption(OptionIndex) || CurrentContext->HasDialogueEnded())
	{
		CurrentContext = nullptr;
		ScreensService->Close();
		DialogueFinished.ExecuteIfBound();
		return;
	}

	DialogueProgressed.ExecuteIfBound();
}

UDlgContext* UDialoguesService::GetCurrentContext()
{
	return CurrentContext;
}
