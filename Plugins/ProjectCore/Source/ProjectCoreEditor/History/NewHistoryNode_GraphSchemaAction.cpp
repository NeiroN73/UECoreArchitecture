// Copyright Floruit, Inc. All Rights Reserved.


#include "NewHistoryNode_GraphSchemaAction.h"

#include "HistoryGraph.h"
#include "GraphNodes/HistoryGraphNode.h"
#include "ProjectCoreRuntime/History/Elements/HistoryElement.h"

UEdGraphNode* FNewHistoryNode_GraphSchemaAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
                                                               const FVector2D Location, bool bSelectNewNode)
{
	const FScopedTransaction Transaction(
		NSLOCTEXT("HistoryEditor", "NewHistoryNode", "History Editor: New History Node"));

	UBaseHistoryElement* InvokerElement = CastChecked<UHistoryGraph>(ParentGraph)->GetElement();
	
	verify(ParentGraph->Modify());

	auto NewNode = NewObject<UHistoryGraphNode>(ParentGraph);
	auto NewElement = NewObject<UHistoryElement>(ParentGraph);
	NewElement->LayerIndex = InvokerElement->LayerIndex + 1;
	NewNode->SetElement(NewElement);

	NewNode->PostEditChange();
	NewNode->MarkPackageDirty();
	NewNode->Modify();
	NewNode->CreateNewGuid();
	NewNode->AllocateDefaultPins();
	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;
    
	ParentGraph->AddNode(NewNode, bSelectNewNode, true);
	
	if (UEdGraphPin* NewInputPin = NewNode->Pins[0])
	{
		if (FromPin && FromPin->LinkedTo.Num() == 0)
		{
			FromPin->MakeLinkTo(NewInputPin);
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}

	NewNode->Modify();
	
	ParentGraph->NotifyGraphChanged();

	return NewNode;
}
