// Copyright Floruit, Inc. All Rights Reserved.


#include "BaseHistoryGraphNode.h"

UBaseHistoryElement* UBaseHistoryGraphNode::GetElement()
{
	return Element;
}

void UBaseHistoryGraphNode::SetElement(UBaseHistoryElement* InElement)
{
	Element = InElement;
}

UEdGraphPin* UBaseHistoryGraphNode::GetInputPin()
{
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin && Pin->Direction == EGPD_Input)
		{
			return Pin;
		}
	}
	return nullptr;
}

TArray<UEdGraphPin*> UBaseHistoryGraphNode::GetOutputPins()
{
	TArray<UEdGraphPin*> OutputPins;
    
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin && Pin->Direction == EGPD_Output)
		{
			OutputPins.Add(Pin);
		}
	}
	return OutputPins;
}
