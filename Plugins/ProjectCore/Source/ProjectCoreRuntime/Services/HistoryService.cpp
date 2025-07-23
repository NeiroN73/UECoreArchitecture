// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryService.h"

#include "PreloadsService.h"
#include "ProjectCoreRuntime/Configs/HistoryConfig.h"
#include "ProjectCoreRuntime/History/Actions/Base/HistoryAction.h"
#include "ProjectCoreRuntime/History/Base/Preloadable.h"
#include "ProjectCoreRuntime/History/Elements/HistoryElement.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/SaveStates/HistorySaveState.h"

void UHistoryService::Inject(TObjectPtr<UInstallerContainer> InContainer)
{
	Container = InContainer;

	HistorySaveState = InContainer->Resolve<UHistorySaveState>();
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
