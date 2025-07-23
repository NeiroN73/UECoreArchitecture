// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryElement.h"

#include "ProjectCoreRuntime/Configs/HistoryConfig.h"
#include "ProjectCoreRuntime/History/Actions/Base/HistoryAction.h"
#include "ProjectCoreRuntime/History/Conditions/Base/HistoryCondition.h"
#include "ProjectCoreRuntime/History/Triggers/Base/HistoryTrigger.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Services/HistoryService.h"

void UHistoryElement::Inject(UInstallerContainer* Container)
{
	HistoryService = Container->Resolve<UHistoryService>();
	HistoryConfig = Container->Resolve<UHistoryConfig>();
    	
	for (const auto& Trigger : Triggers)
	{
		Trigger->Inject(Container);
	}
	for (const auto& Action : Actions)
	{
		Action->Inject(Container);
	}
	for (const auto& Condition : Conditions)
	{
		Condition->Inject(Container);
	}
}

void UHistoryElement::Initialize()
{
	for (const auto& Trigger : Triggers)
	{
		Trigger->Bind();
		Trigger->OnTriggered.BindLambda([this]
		{
			TryProgress();
		});
	}

	bInitialized = true;
}

void UHistoryElement::TryProgress()
{
	if (!TryProcessTriggers())
	{
		return;
	}
	ProcessActions();
	ProcessConditions();
}

bool UHistoryElement::TryProcessTriggers()
{
	for (const auto& Trigger : Triggers)
	{
		if (!Trigger || !Trigger->bTriggered)
		{
			return false;
		}
	}
	return true;
}

void UHistoryElement::ProcessActions()
{
	for (const auto& Action : Actions)
	{
		if (Action)
		{
			Action->Execute();
		}
	}
}

void UHistoryElement::ProcessConditions()
{
	for (const auto& Condition : Conditions)
	{
		Condition->OnCompleted.BindUObject(this, &UHistoryElement::OnConditionCompleted);
		Condition->Check();
	}
}

void UHistoryElement::OnConditionCompleted()
{
	if (bOnlyFirstConditionComplete)
	{
		Complete();
	}
			
	for (const auto& Condition : Conditions)
	{
		if (!Condition->bCompleted)
		{
			break;
		}

		Complete();
	}
}

void UHistoryElement::Complete()
{
	State = EElementState::Completed;
	HistoryService->TryProgress();
	Disable();
}

void UHistoryElement::Disable()
{
	for (const auto& Trigger : Triggers)
	{
		Trigger->OnTriggered.Unbind();
	}
	for (const auto& Condition : Conditions)
	{
		Condition->OnCompleted.Unbind();
	}
}
