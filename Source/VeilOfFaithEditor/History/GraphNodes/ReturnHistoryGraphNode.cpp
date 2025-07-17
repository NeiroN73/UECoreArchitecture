// Copyright Floruit, Inc. All Rights Reserved.


#include "ReturnHistoryGraphNode.h"

#include "UObject/ObjectSaveContext.h"
#include "VeilOfFaith/History/Elements/ReturnHistoryElement.h"
#include "VeilOfFaithEditor/History/HistoryGraph.h"

FText UReturnHistoryGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("HistoryGraph", "ReturnNodeTitle", "Return Node");
}

FText UReturnHistoryGraphNode::GetTooltipText() const
{
	return NSLOCTEXT("HistoryGraph", "ReturnNodeTitle", "Return this node in current layer");
}

void UReturnHistoryGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName());
}

void UReturnHistoryGraphNode::NodeConnectionListChanged()
{
	const FScopedTransaction Transaction(FText::FromString("Return Node Connection"));
	
	Modify();
	GetGraph()->NotifyGraphChanged();
}

FLinearColor UReturnHistoryGraphNode::GetNodeTitleColor() const
{
	return FColor(150, 0, 10);
}

UBaseHistoryElement* UReturnHistoryGraphNode::GetElement()
{
	return ReturnElement;
}

void UReturnHistoryGraphNode::SetElement(UBaseHistoryElement* InElement)
{
	Super::SetElement(InElement);

	ReturnElement = Cast<UReturnHistoryElement>(InElement);

	auto HistoryGraph = Cast<UHistoryGraph>(GetGraph());
	HistoryGraph->UpdateElementData();
}

void UReturnHistoryGraphNode::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);

	auto HistoryGraph = Cast<UHistoryGraph>(GetGraph());
	HistoryGraph->UpdateElementData();
}

bool UReturnHistoryGraphNode::CanUserDeleteNode() const
{
	return false;
}

void UReturnHistoryGraphNode::PostLoad()
{
	Super::PostLoad();

	auto HistoryGraph = Cast<UHistoryGraph>(GetGraph());
	HistoryGraph->UpdateElementData();
}
