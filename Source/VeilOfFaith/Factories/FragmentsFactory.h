// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "FragmentsFactory.generated.h"

class IInitializable;
class UFragment;

DECLARE_DELEGATE_TwoParams(FOnFragmentAdded, TSubclassOf<UFragment>, UFragment*)

UCLASS()
class VEILOFFAITH_API UFragmentsFactory : public UBaseFactory
{
	GENERATED_BODY()

public:
	FOnFragmentAdded OnFragmentAdded;
	
	template<typename TFragment = UFragment>
	TFragment* Create()
	{
		auto Fragment = NewObject<TFragment>(World);
		CastInjectable(Fragment);
		CastTickable(Fragment);
		OnFragmentAdded.ExecuteIfBound(TFragment::StaticClass(), Fragment);
		return Fragment;
	}
};
