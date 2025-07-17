// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "VeilOfFaith/History/Elements/Base/BaseHistoryElement.h"
#include "BaseHistoryGraphNode.generated.h"

class UBaseHistoryElement;

UCLASS(Abstract)
class VEILOFFAITHEDITOR_API UBaseHistoryGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UBaseHistoryElement> Element;

public:
	virtual UBaseHistoryElement* GetElement();
	virtual void SetElement(UBaseHistoryElement* InElement);

	UEdGraphPin* GetInputPin();
	TArray<UEdGraphPin*> GetOutputPins();
};
