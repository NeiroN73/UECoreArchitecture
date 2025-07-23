// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "Base/PreloadConfig.h"
#include "ProjectCoreRuntime/EditorUtils/CustomId.h"
#include "DialoguesConfig.generated.h"

class UDlgDialogue;
class UPreloadsService;

UCLASS()
class PROJECTCORERUNTIME_API UDialoguesConfig : public UConfig,
public IPreloadConfig
{
	GENERATED_BODY()

public:
	virtual TMap<FName, FSoftObjectPath> GetSoftPaths() override;

	UPROPERTY(EditAnywhere)
	TMap<FCustomId, TSoftObjectPtr<UDlgDialogue>> DialoguesById;
};
