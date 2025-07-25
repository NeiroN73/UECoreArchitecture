// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "HistoryGraph.generated.h"

class URootHistoryElement;
class UHistoryGraphNode;
class UBaseHistoryElement;
class UHistoryGraphSchema;

UCLASS()
class VEILOFFAITHEDITOR_API UHistoryGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UHistoryGraph();

	UBaseHistoryElement* GetElement() const;
	const UHistoryGraphSchema* GetDialogueGraphSchema() const;
	void UpdateElementData();

	UPROPERTY()
	TObjectPtr<UHistoryGraphNode> Node;
	UPROPERTY()
	TObjectPtr<UBaseHistoryElement> Element;
	UPROPERTY()
	TWeakObjectPtr<URootHistoryElement> RootElement;
};
