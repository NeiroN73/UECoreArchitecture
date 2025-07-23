// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/EditorUtils/EditorAccessable.h"
#include "EditorAccess.generated.h"

UCLASS()
class PROJECTCOREEDITOR_API UEditorAccess : public UObject, public IEditorAccessable
{
	GENERATED_BODY()

public:
	virtual UEdGraph* CreateHistoryGraph(UBaseHistoryElement* HistoryElement) override;
};
