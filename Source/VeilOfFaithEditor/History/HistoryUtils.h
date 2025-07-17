// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GraphNodes/BaseHistoryGraphNode.h"
#include "VeilOfFaith/History/Elements/RootHistoryElement.h"

class VEILOFFAITHEDITOR_API FHistoryUtils
{
public:
	template<class TNode = UBaseHistoryGraphNode, class TElement = UBaseHistoryElement>
	static TArray<TElement*> FindElements(URootHistoryElement* RootElement, UBaseHistoryElement* ParentElement)
	{
		TArray<TElement*> OutElements;
		
		if (RootElement && ParentElement)
		{
			TArray<TNode*> OutGraphNodes = FindNodes<TNode>(RootElement->GetGraph(ParentElement));

			for (auto OutGraphNode : OutGraphNodes)
			{
				if (OutGraphNode)
				{
					if (auto InElement = Cast<TElement>(OutGraphNode->GetElement()))
					{
						OutElements.Add(InElement);
					}
				}
			}
		}

		return OutElements;
	}

	template<class TNode = UBaseHistoryGraphNode>
	static TArray<TNode*> FindNodes(UEdGraph* Graph)
	{
		TArray<TNode*> OutGraphNodes;
		if (Graph)
		{
			Graph->GetNodesOfClass<TNode>(OutGraphNodes);
		}

		return OutGraphNodes;
	}
};
