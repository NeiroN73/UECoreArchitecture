// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/SaveState.h"
#include "VeilOfFaith/Installer/Initializable.h"
#include "VeilOfFaith/Installer/Injectable.h"
#include "HistorySaveState.generated.h"

class UHistoryElement;
class UBaseHistoryElement;
class UHistoryConfig;

UCLASS()
class VEILOFFAITH_API UHistorySaveState : public USaveState,
public IInjectable,
public IInitializable
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TSet<TObjectPtr<UHistoryElement>> CurrentElements;
	UPROPERTY()
	TSet<TObjectPtr<UHistoryElement>> AllElements;
	
	virtual void Read() override;
	virtual void Write() override;
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	virtual void Initialize() override;

	void GatherElementsRecursive(const UBaseHistoryElement* ParentElement, TSet<UHistoryElement*>& OutElements);
	void GatherCurrentElementsRecursive(const UBaseHistoryElement* ParentElement);
	void UpdateCurrentElements();

private:
	UPROPERTY()
	TObjectPtr<UHistoryConfig> HistoryConfig;
};
