// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CustomId.generated.h"

USTRUCT()
struct VEILOFFAITH_API FCustomId
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Id"))
	FName IdName;

	UPROPERTY(EditAnywhere, Category="Editor", meta = (DisplayName = "Added Id"));
	FName AddedIdName;

	UPROPERTY(EditAnywhere, Category="Editor", meta = (DisplayName = "Removed Id"))
	FName RemovedIdName;

public:
	FCustomId() : IdName(NAME_None) {}

	FCustomId(const FName& Name) : IdName(Name) {}

	FCustomId(const FCustomId& Other) : IdName(Other.IdName) {}

	operator FName() const
	{
		return IdName;
	}

	friend uint32 GetTypeHash(const FCustomId& Id)
	{
		return GetTypeHash(Id.IdName);
	}

	friend FString ToString(const FCustomId& Id)
	{
		return Id.IdName.ToString();
	}
    
	bool operator==(const FName& Other) const
	{
		return IdName == Other;
	}

	bool operator==(const FCustomId& Other) const
	{
		return IdName == Other.IdName;
	}
    
	bool operator!=(const FName& Other) const
	{
		return IdName != Other;
	}

	bool operator!=(const FCustomId& Other) const
	{
		return IdName != Other.IdName;
	}

	bool operator=(const FCustomId& Other) const
	{
		return IdName == Other.IdName;
	}

	bool operator=(const FName& Other) const
	{
		return IdName == Other;
	}
};