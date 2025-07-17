// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class VEILOFFAITHEDITOR_API FLogger
{
public:
	static void ShowMessage(const FString& Message);
	static void ShowNotification(const FString& Message);
};
