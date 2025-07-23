// Copyright Floruit, Inc. All Rights Reserved.


#include "HandlersConfig.h"

void UHandlersConfig::Initialize()
{
	for (auto Handler : Handlers)
	{
		HandlersById.Add(Handler->GetFName(), Handler);
	}
}
