// Copyright Floruit, Inc. All Rights Reserved.


#include "HistorySaveState.h"

#include "ProjectCoreRuntime/Configs/HistoryConfig.h"
#include "ProjectCoreRuntime/History/Conditions/Base/HistoryCondition.h"
#include "ProjectCoreRuntime/History/Elements/RootHistoryElement.h"
#include "ProjectCoreRuntime/History/Elements/HistoryElement.h"
#include "ProjectCoreRuntime/History/Elements/ReturnHistoryElement.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"

void UHistorySaveState::Inject(TObjectPtr<UInstallerContainer> Container)
{
	HistoryConfig = Container->Resolve<UHistoryConfig>();
}

void UHistorySaveState::Initialize()
{
	UpdateCurrentElements();
}

void UHistorySaveState::GatherElementsRecursive(const UBaseHistoryElement* ParentElement,
	TSet<UHistoryElement*>& OutElements)
{
	for (auto Element : ParentElement->ChildElements)
	{
		OutElements.Add(Element);
		GatherElementsRecursive(Element, OutElements);
	}
}

void UHistorySaveState::GatherCurrentElementsRecursive(const UBaseHistoryElement* ParentElement)
{
	TSet<UBaseHistoryElement*> RemoveElementsSet;

	for (auto Element : ParentElement->ChildElements)
	{
		if (Element->State == EElementState::Completed)
			continue;

		if (Element->State == EElementState::Skipped)
			continue;

		for (auto Condition : Element->Conditions)
		{
			if (Condition && Condition->NextElementId.IsValid())
			{
				if (auto NextElement = HistoryConfig->GetElement(Condition->NextElementId))
				{
					if (auto ReturnElement = Cast<UReturnHistoryElement>(NextElement))
					{
						auto cElements = ParentElement->ReturnElement->ParentElement->ChildElements;
						for (auto cElement : cElements)
						{
							cElement->State = EElementState::Skipped;
							RemoveElementsSet.Add(cElement);
							RemoveElementsSet.Add(ParentElement->ReturnElement);
						}
						ReturnElement->State = EElementState::Completed;
					}
					RemoveElementsSet.Add(NextElement);
				}
			}
		}
	}
	
	for (auto Element : ParentElement->ChildElements)
	{
		if (RemoveElementsSet.Contains(Element))
			continue;
        
		CurrentElements.Add(Element);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1000, FColor::Green,
				FString::Printf(TEXT("Current elements: %s"), *Element->GetName()));
		}
        
		GatherCurrentElementsRecursive(Element);
	}
}

void UHistorySaveState::UpdateCurrentElements()
{
	for (auto Element : CurrentElements)
	{
		Element->bInitialized = false;
	}
	CurrentElements.Empty();
	GatherCurrentElementsRecursive(HistoryConfig->RootHistoryElement);

	for (auto Element : CurrentElements)
	{
		if (GEngine && Element)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,
FString::Printf(TEXT("Currents elements: %s"), *Element->GetName()));
		}
	}
}

void UHistorySaveState::Read()
{
	for (auto Id : SaveGame->HistorySaveData.CurrentElementIds)
	{
		if (auto Element = HistoryConfig->GetElement<UHistoryElement>(Id))
		{
			CurrentElements.Add(Element);
		}
	}
}

void UHistorySaveState::Write()
{
	SaveGame->HistorySaveData = FHistorySaveData();
	for (auto Element : CurrentElements)
	{
		SaveGame->HistorySaveData.CurrentElementIds.Add(Element->Guid);
	}
}
