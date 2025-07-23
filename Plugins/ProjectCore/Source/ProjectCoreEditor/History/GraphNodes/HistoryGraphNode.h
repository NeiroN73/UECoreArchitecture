// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseHistoryGraphNode.h"
#include "EdGraph/EdGraphNode.h"
#include "HistoryGraphNode.generated.h"

class UHistoryConfig;
class UHistoryElement;

UCLASS()
class PROJECTCOREEDITOR_API UHistoryGraphNode : public UBaseHistoryGraphNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UHistoryElement> HistoryElement;
	
public:
	virtual void PostLoad() override;
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual void AllocateDefaultPins() override;
	virtual void NodeConnectionListChanged() override;

	virtual FLinearColor GetNodeTitleColor() const override;

	virtual void PreSave(FObjectPreSaveContext SaveContext) override;

	virtual void SetElement(UBaseHistoryElement* Element) override;
	virtual UBaseHistoryElement* GetElement() override;

	void UpdateElementData();
	void UpdatePins();
};
