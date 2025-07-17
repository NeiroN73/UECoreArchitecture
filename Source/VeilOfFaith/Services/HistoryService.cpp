// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryService.h"

#include "DialoguesService.h"
#include "PreloadsService.h"
#include "VeilOfFaith/Configs/HistoryConfig.h"
#include "VeilOfFaith/History/Actions/Base/HistoryAction.h"
#include "VeilOfFaith/History/Base/Preloadable.h"
#include "VeilOfFaith/History/Elements/HistoryElement.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/SaveStates/HistorySaveState.h"

void UHistoryService::Inject(TObjectPtr<UInstallerContainer> InContainer)
{
	Container = InContainer;

	HistorySaveState = InContainer->Resolve<UHistorySaveState>();
	DialoguesService = InContainer->Resolve<UDialoguesService>();
	HistoryConfig = InContainer->Resolve<UHistoryConfig>();
	PreloadsService = InContainer->Resolve<UPreloadsService>();
}

void UHistoryService::TryProgress()
{
	HistorySaveState->UpdateCurrentElements();

	TSet<FName> PreloadIds;
	for (auto Element : HistorySaveState->CurrentElements)
	{
		if (auto HistoryElement = Cast<UHistoryElement>(Element))
		{
			if (HistoryElement->bRootPreloadable)
			{
				TSet<UHistoryElement*> OutElements;
				HistorySaveState->GatherElementsRecursive(Element, OutElements);
				for (auto OutElement : OutElements)
				{
					for (auto Action : OutElement->Actions)
					{
						if (auto Preload= Cast<IPreloadable>(Action))
						{
							PreloadIds.Append(Preload->GetPreloadIds());
						}
					}
				}
			}
		}
	}
	PreloadsService->StartPreload(PreloadIds, FOnPreloadCompleted::CreateUObject(this,
		&UHistoryService::OnPreloadsLoaded));
}

void UHistoryService::OnPreloadsLoaded()
{
	for (auto Element : HistorySaveState->CurrentElements)
	{
		if (Element)
		{
			if (Element->bInitialized)
			{
				continue;
			}

			Element->Inject(Container);
			Element->Initialize();
		}
	}
}
