// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryGraphSchema.h"

#include "HistoryUtils.h"
#include "NewHistoryNode_GraphSchemaAction.h"
#include "GraphNodes/ReturnHistoryGraphNode.h"
#include "ProjectCoreRuntime/History/Elements/ReturnHistoryElement.h"

void UHistoryGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("HistoryEditor", "CreateDefaultReturnNode",
		"Create Default Return Node"));
    
	auto ReturnNodes = FHistoryUtils::FindNodes<UReturnHistoryGraphNode>(&Graph);
	if (ReturnNodes.Num() == 0)
	{
		Graph.Modify();
        
		UReturnHistoryGraphNode* ReturnNode = NewObject<UReturnHistoryGraphNode>(&Graph);
        
		auto NewElement = NewObject<UReturnHistoryElement>(&Graph);
		ReturnNode->SetElement(NewElement);
        
		ReturnNode->CreateNewGuid();
		ReturnNode->AllocateDefaultPins();
		ReturnNode->PostEditChange();
        
		ReturnNode->NodePosX = 0;
		ReturnNode->NodePosY = 0;
        
		Graph.AddNode(ReturnNode, false, true);
        
		ReturnNode->MarkPackageDirty();
		ReturnNode->Modify();
        
		Graph.NotifyGraphChanged();
	}
}

void UHistoryGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FNewHistoryNode_GraphSchemaAction> Action_HistoryNode = MakeShareable(
		new FNewHistoryNode_GraphSchemaAction(
			FText::FromName(FName("Graph")),
			FText::FromName(FName("History Node")),
			FText::FromName(FName("Create History Node")), 0)
	);
	
	ContextMenuBuilder.AddAction(Action_HistoryNode);
}

const FPinConnectionResponse UHistoryGraphSchema::CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const
{
    if (!PinA || !PinB || PinA->GetOwningNode() == PinB->GetOwningNode())
    {
        return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Invalid connection"));
    }

    if (PinA->Direction == PinB->Direction)
    {
        return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Directions are incompatible"));
    }

    return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

bool UHistoryGraphSchema::TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
    if (CanCreateConnection(PinA, PinB).Response != CONNECT_RESPONSE_MAKE)
    {
        return false;
    }

    UEdGraphPin* InputPin = PinA->Direction == EGPD_Input ? PinA : PinB;
    UEdGraphPin* OutputPin = PinA->Direction == EGPD_Output ? PinA : PinB;

    if (InputPin->LinkedTo.Num() > 0)
    {
        InputPin->BreakAllPinLinks();
    }
	
	if (OutputPin->LinkedTo.Num() > 0)
	{
		OutputPin->BreakAllPinLinks();
	}

    InputPin->Modify();
    OutputPin->Modify();
	
    InputPin->MakeLinkTo(OutputPin);

    InputPin->GetOwningNode()->GetGraph()->NotifyGraphChanged();
	
    return true;
}

FLinearColor UHistoryGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FLinearColor::White; 
}
