// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VeilOfFaith/EditorUtils/CustomId.h"
#include "TableData.generated.h"

USTRUCT()
struct VEILOFFAITH_API FTableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FCustomId Id;
};
