// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VeilOfFaith/TableConfigs/Base/TableData.h"
#include "HistoryTableData.generated.h"

struct FHistoryNodeDataTable;

USTRUCT()
struct VEILOFFAITH_API FHistoryTableData : public FTableData
{
	GENERATED_BODY()

	TArray<FName> PrevNodeIds;
	TArray<FName> NextNodeIds;
	TArray<FName> DelegateIds;
	TArray<FName> FunctionIds;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHistoryNodeDataTable> Nodes;
};
