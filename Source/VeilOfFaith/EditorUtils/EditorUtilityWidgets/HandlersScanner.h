// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "HandlersScanner.generated.h"

class AGameplayGameMode;
class AInstallerGameMode;
class UButton;

UCLASS()
class VEILOFFAITH_API UHandlersScanner : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta= (BindWidget))
	UButton* AssetPathsButton;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void GenerateScriptAssetPaths();
	UFUNCTION()
	void GenerateScriptIds();
};
