// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Config.h"
#include "ProjectCoreRuntime/Installer/Initializable.h"
#include "HistoryConfig.generated.h"


class UBaseHistoryElement;
class URootHistoryElement;

UCLASS()
class PROJECTCORERUNTIME_API UHistoryConfig : public UConfig,
public IInitializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<URootHistoryElement> RootHistoryElement;
	
	TMap<FGuid, TObjectPtr<UBaseHistoryElement>> Elements;

	template<typename TElement = UBaseHistoryElement>
	TElement* GetElement(FGuid ElementId)
	{
		if (auto Element = Elements.FindRef(ElementId))
		{
			return Cast<TElement>(Element);
		}
		return nullptr;
	}

	virtual void Initialize() override;
};
