// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VeilOfFaith/EditorUtils/EditorAccessable.h"
#include "EditorAccess.generated.h"

UCLASS()
class VEILOFFAITHEDITOR_API UEditorAccess : public UObject, public IEditorAccessable
{
	GENERATED_BODY()

public:
	virtual UEdGraph* CreateHistoryGraph(UBaseHistoryElement* HistoryElement) override;
};
