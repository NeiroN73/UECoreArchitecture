// Copyright Floruit, Inc. All Rights Reserved.


#include "InstallerContainer.h"

void UInstallerContainer::Register(UObject* Object)
{
	if (Object)
	{
		UClass* InClass = Object->GetClass();
		if (!Registrations.Contains(InClass)) 
		{
			Registrations.Add(InClass, Object);
		}
	}
}
