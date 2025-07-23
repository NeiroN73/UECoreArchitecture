// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/TableData.h"
#include "DialoguesTableData.generated.h"

class UDlgDialogue;

USTRUCT()
struct PROJECTCORERUNTIME_API FDialoguesTableData : public FTableData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDlgDialogue> Dialogue;
};
