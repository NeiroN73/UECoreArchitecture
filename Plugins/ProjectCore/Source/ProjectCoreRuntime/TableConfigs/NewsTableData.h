// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/TableData.h"
#include "NewsTableData.generated.h"

USTRUCT()
struct PROJECTCORERUNTIME_API FNewsTableData : public FTableData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString MyString;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
};