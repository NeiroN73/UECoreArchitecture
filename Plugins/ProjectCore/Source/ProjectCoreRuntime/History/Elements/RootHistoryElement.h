// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseHistoryElement.h"
#include "UObject/ObjectSaveContext.h"
#include "RootHistoryElement.generated.h"

DECLARE_DELEGATE(FOnElementSaved)

UCLASS()
class PROJECTCORERUNTIME_API URootHistoryElement : public UBaseHistoryElement
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<FGuid, TObjectPtr<UBaseHistoryElement>> Elements;
	
#if WITH_EDITORONLY_DATA
public:
	FOnElementSaved OnElementSaved;
	
	UPROPERTY()
	TMap<TObjectPtr<UBaseHistoryElement>, TObjectPtr<UEdGraph>> EdGraphsByElement;

	template<class TEdGraph = UEdGraph>
	TEdGraph* GetGraph(UBaseHistoryElement* Element)
	{
		if (auto Graph = EdGraphsByElement.FindRef(Element))
		{
			if (auto CastGraph = Cast<TEdGraph>(Graph))
			{
				return CastGraph;
			}
		}
		return nullptr;
	}
	
	virtual void PreSave(FObjectPreSaveContext SaveContext) override
	{
		Super::PreSave(SaveContext);

		OnElementSaved.Execute();
	}
#endif
};
