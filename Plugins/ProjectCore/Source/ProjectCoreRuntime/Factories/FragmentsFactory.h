// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseFactory.h"
#include "ProjectCoreRuntime/Fragments/Base/Fragment.h"
#include "FragmentsFactory.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UFragmentsFactory : public UBaseFactory
{
	GENERATED_BODY()

public:
	template<typename TFragment = UFragment>
	TFragment* Create()
	{
		auto Fragment = NewObject<TFragment>(World);
		CastInjectable(Fragment);
		CastTickable(Fragment);
		return Fragment;
	}
};
