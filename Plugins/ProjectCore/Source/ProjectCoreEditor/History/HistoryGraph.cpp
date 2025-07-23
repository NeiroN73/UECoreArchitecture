// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryGraph.h"

#include "HistoryGraphSchema.h"
#include "HistoryUtils.h"
#include "GraphNodes/HistoryGraphNode.h"
#include "GraphNodes/ReturnHistoryGraphNode.h"
#include "ProjectCoreRuntime/History/Elements/HistoryElement.h"
#include "ProjectCoreRuntime/History/Elements/ReturnHistoryElement.h"
#include "ProjectCoreRuntime/History/Elements/Base/BaseHistoryElement.h"


UBaseHistoryElement* UHistoryGraph::GetElement() const
{
	return Element;
}

const UHistoryGraphSchema* UHistoryGraph::GetDialogueGraphSchema() const
{
	return GetDefault<UHistoryGraphSchema>(Schema);
}

void UHistoryGraph::UpdateElementData()
{
	if (!Element)
	{
		Element = CastChecked<UBaseHistoryElement>(GetOuter());
	}
	if (Element)
	{
		Element->ChildElements.Empty();
		
		auto ReturnElements =
			FHistoryUtils::FindElements<UReturnHistoryGraphNode, UReturnHistoryElement>(RootElement.Get(), Element);
		for (auto InElement : ReturnElements)
		{
			InElement->ParentElement = Element;
			Element->ReturnElement = InElement;
		}
		
		auto Elements =
			FHistoryUtils::FindElements<UHistoryGraphNode, UHistoryElement>(RootElement.Get(), Element);
		for (auto InElement : Elements)
		{
			Element->ChildElements.Add(InElement);
		}
	}
}
