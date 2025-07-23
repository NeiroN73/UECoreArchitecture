// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "TableData.generated.h"

USTRUCT()
struct PROJECTCORERUNTIME_API FTableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FCustomId Id;
};
