// Copyright Floruit, Inc. All Rights Reserved.


#include "EditorAccess.h"

#include "HistoryGraph.h"
#include "HistoryGraphSchema.h"
#include "ProjectCoreRuntime/History/Elements/HistoryElement.h"

UEdGraph* UEditorAccess::CreateHistoryGraph(UBaseHistoryElement* Element)
{
	UHistoryGraph* Graph = NewObject<UHistoryGraph>(Element, UHistoryGraph::StaticClass(),
		TEXT("HistoryGraph"), RF_Transactional);
	Graph->Schema = UHistoryGraphSchema::StaticClass();
	Graph->bAllowDeletion = false;
	if (auto EdGraph = Cast<UEdGraph>(Graph))
	{
		return EdGraph;
	}
	return nullptr;
}
