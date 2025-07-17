// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EditorAccessable.generated.h"

class UBaseHistoryElement;

UINTERFACE()
class UEditorAccessable : public UInterface
{
	GENERATED_BODY()
};

class VEILOFFAITH_API IEditorAccessable
{
	GENERATED_BODY()

public:
	virtual UEdGraph* CreateHistoryGraph(UBaseHistoryElement* HistoryElement) = 0;
};
