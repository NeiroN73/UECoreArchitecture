// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseHistoryGraphNode.h"
#include "EdGraph/EdGraphNode.h"
#include "ReturnHistoryGraphNode.generated.h"

class UReturnHistoryElement;
class UBaseHistoryElement;

UCLASS()
class VEILOFFAITHEDITOR_API UReturnHistoryGraphNode : public UBaseHistoryGraphNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UReturnHistoryElement> ReturnElement;
	
public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual void AllocateDefaultPins() override;
	virtual void NodeConnectionListChanged() override;
	virtual FLinearColor GetNodeTitleColor() const override;

	virtual UBaseHistoryElement* GetElement() override;
	virtual void SetElement(UBaseHistoryElement* InElement) override;

	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	virtual bool CanUserDeleteNode() const override;
	virtual void PostLoad() override;
};
