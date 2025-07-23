// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryGraphNode.h"

#include "ReturnHistoryGraphNode.h"
#include "UObject/ObjectSaveContext.h"
#include "ProjectCoreRuntime/History/Conditions/Base/HistoryCondition.h"
#include "ProjectCoreRuntime/History/Elements/RootHistoryElement.h"
#include "ProjectCoreRuntime/History/Elements/HistoryElement.h"
#include "ProjectCoreEditor/History/HistoryGraph.h"

void UHistoryGraphNode::PostLoad()
{
	Super::PostLoad();

	UpdateElementData();
}

FText UHistoryGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (HistoryElement && HistoryElement->Name != NAME_None)
	{
		return FText::FromString(HistoryElement->Name.ToString());
	}
	return NSLOCTEXT("HistoryGraph", "EmptyNodeTitle", "History Node");
}

FText UHistoryGraphNode::GetTooltipText() const
{
	if (HistoryElement && HistoryElement->Name != NAME_None)
	{
		return FText::FromString(HistoryElement->Description.ToString());
	}
	return NSLOCTEXT("HistoryGraph", "EmptyNodeTitle", "History Node Description");
}

void UHistoryGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName());
}

void UHistoryGraphNode::NodeConnectionListChanged()
{
	Super::NodeConnectionListChanged();

	const FScopedTransaction Transaction(FText::FromString("Modify Node Connections"));

	TArray<UEdGraphPin*> OutputPins;
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin && Pin->Direction == EGPD_Output)
		{
			OutputPins.Add(Pin);
		}
	}

	for (int32 It = 0; It < OutputPins.Num(); ++It)
	{
		auto InPin = OutputPins[It];
		
		if (HistoryElement && 
			HistoryElement->Conditions.IsValidIndex(It) &&
			HistoryElement->Conditions[It])
		{
			if (InPin->LinkedTo.Num() == 0)
			{
				HistoryElement->Conditions[It]->NextElementId.Invalidate();
			}
			else
			{
				for (UEdGraphPin* LinkedPin : InPin->LinkedTo)
				{
					if (UBaseHistoryGraphNode* ConnectedNode = Cast<UBaseHistoryGraphNode>(LinkedPin->GetOwningNode()))
					{
						if (auto InElement = ConnectedNode->GetElement())
						{
							HistoryElement->Conditions[It]->NextElementId = InElement->Guid;
							break;
						}
					}
				}
			}
		}
	}

	Modify();
	GetGraph()->NotifyGraphChanged();
}

FLinearColor UHistoryGraphNode::GetNodeTitleColor() const
{
	return FColor(128, 0, 128);
}

void UHistoryGraphNode::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);

	UpdateElementData();
}

void UHistoryGraphNode::SetElement(UBaseHistoryElement* InElement)
{
	Super::SetElement(InElement);
	
	HistoryElement = Cast<UHistoryElement>(InElement);

	UpdateElementData();
}

UBaseHistoryElement* UHistoryGraphNode::GetElement()
{
	return HistoryElement;
}

void UHistoryGraphNode::UpdateElementData()
{
	HistoryElement->OnElementPropertyChanged.Unbind();
	HistoryElement->OnElementPropertyChanged.BindLambda([this]
	{
		UpdatePins();
	});
	auto HistoryGraph = Cast<UHistoryGraph>(GetGraph());
	HistoryGraph->UpdateElementData();
}

void UHistoryGraphNode::UpdatePins()
{
	const FScopedTransaction Transaction(FText::FromString("Update Node Pins"));

	TArray<UEdGraphPin*> PinsToRemove = GetOutputPins();
	
	for (UEdGraphPin* Pin : PinsToRemove)
	{
		Pin->Modify();
		RemovePin(Pin);
	}

	if (HistoryElement)
	{
		HistoryElement->Modify();
		for (int32 It = 0; It < HistoryElement->Conditions.Num(); ++It)
		{
			if (auto Condition = HistoryElement->Conditions[It])
			{
				Condition->Modify();
                
				auto PinName = Condition->GetClass()->GetFName();
				UEdGraphPin* NewPin = CreatePin(EGPD_Output, "MultipleNodes", PinName);

				for (auto Node : GetGraph()->Nodes)
				{
					if (auto HistoryNode = Cast<UBaseHistoryGraphNode>(Node))
					{
						if (Condition)
						{
							if (auto InElement = HistoryNode->GetElement())
							{
								if (Condition->NextElementId == InElement->Guid)
								{
									HistoryNode->GetInputPin()->MakeLinkTo(GetOutputPins()[It]);
								}
							}
						}
					}
				}
				
				NewPin->Modify();
			}
		}
	}

	Modify();
	GetGraph()->NotifyGraphChanged();
}

