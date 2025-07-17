// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryGraph.h"

#include "EditorAccess.h"
#include "HistoryGraphSchema.h"
#include "HistoryUtils.h"
#include "GraphNodes/HistoryGraphNode.h"
#include "GraphNodes/ReturnHistoryGraphNode.h"
#include "VeilOfFaith/History/Elements/HistoryElement.h"
#include "VeilOfFaith/History/Elements/ReturnHistoryElement.h"
#include "VeilOfFaith/History/Elements/Base/BaseHistoryElement.h"

UHistoryGraph::UHistoryGraph()
{
	// if (!UBaseHistoryElement::EditorAccess.IsValid())
	// {
	// 	UBaseHistoryElement::EditorAccess = TSharedPtr<IEditorAccessable>(NewObject<UEditorAccess>());
	// }
}

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
