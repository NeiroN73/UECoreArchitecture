// Copyright Floruit, Inc. All Rights Reserved.


#include "TickService.h"


void UTickService::Tick(float DeltaSeconds)
{
	for (auto Tickable : Tickables)
	{
		if (Tickable)
		{
			Tickable->Tick(DeltaSeconds);
		}
		else
		{
			Tickables.Remove(Tickable);
		}
	}
}

void UTickService::RegisterTick(ITickable* Tickable)
{
	if (Tickable != this)
	{
		Tickables.Add(Tickable);
	}
}
