// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseHistoryElement.h"
#include "UObject/Object.h"
#include "HistoryElement.generated.h"

class UHistoryConfig;
class UHistoryAction;
class UHistoryService;
class UHistoryCondition;
class UInstallerContainer;
class UHistoryTrigger;

UCLASS()
class PROJECTCORERUNTIME_API UHistoryElement : public UBaseHistoryElement
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName Name;
	UPROPERTY(EditAnywhere)
	FName Description;
	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UHistoryTrigger>> Triggers;
	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UHistoryAction>> Actions;
	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UHistoryCondition>> Conditions;
	UPROPERTY(EditAnywhere)
	bool bRootPreloadable;
	UPROPERTY(EditAnywhere)
	bool bOnlyFirstConditionComplete;
	
	UPROPERTY(Transient)
	bool bInitialized = false;
	UPROPERTY()
	TObjectPtr<UHistoryService> HistoryService;
	UPROPERTY()
	TObjectPtr<UHistoryConfig> HistoryConfig;

	virtual void Inject(UInstallerContainer* Container);
	virtual void Initialize();
	virtual void TryProgress();
	virtual void Disable();

protected:
	virtual bool TryProcessTriggers();
	virtual void ProcessActions();
	virtual void ProcessConditions();

	void OnConditionCompleted();
	void Complete();
	
#if WITH_EDITOR
public:

	DECLARE_DELEGATE(FOnElementPropertyChanged)
	FOnElementPropertyChanged OnElementPropertyChanged;
	
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override
	{
		Super::PostEditChangeProperty(PropertyChangedEvent);

		OnElementPropertyChanged.ExecuteIfBound();
	}
#endif
};
