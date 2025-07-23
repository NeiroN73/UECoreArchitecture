// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class VEILOFFAITHEDITOR_API FVeilOfFaithEditor : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
};
