// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "NewHistoryNode_GraphSchemaAction.generated.h"

class UHistoryElement;
class UHistoryAsset;

USTRUCT()
struct PROJECTCOREEDITOR_API FNewHistoryNode_GraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_BODY()
	
public:
	FNewHistoryNode_GraphSchemaAction() {}
	FNewHistoryNode_GraphSchemaAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip,
		int32 InGrouping) : FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping) {}
	
	UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
		const FVector2D Location, bool bSelectNewNode = true) override;
};
