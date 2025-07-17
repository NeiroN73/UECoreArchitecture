// Copyright Floruit, Inc. All Rights Reserved.


#include "BaseFactory.h"

#include "VeilOfFaith/Installer/Initializable.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Services/TickService.h"
#include "VeilOfFaith/Services/Base/Fragmentable.h"
#include "VeilOfFaith/Services/Base/Tickable.h"

void UBaseFactory::Inject(TObjectPtr<UInstallerContainer> Container)
{
	InstallerContainer = Container;

	TickService = Container->Resolve<UTickService>();
	FragmentsFactory = Container->Resolve<UFragmentsFactory>();
}

void UBaseFactory::WorldChanged(UWorld* NewWorld)
{
	World = NewWorld;
}

void UBaseFactory::CastInterfaces(UObject* Object)
{
	CastInjectable(Object);
	CastModulable(Object);
	CastInitializable(Object);
	CastTickable(Object);
}

void UBaseFactory::CastInjectable(UObject* Object)
{
	if (auto Injectable = Cast<IInjectable>(Object))
	{
		Injectable->Inject(InstallerContainer);
	}
}

void UBaseFactory::CastInitializable(UObject* Object)
{
	if (auto Initializable = Cast<IInitializable>(Object))
	{
		Initializable->Initialize();
	}
}

void UBaseFactory::CastTickable(UObject* Object)
{
	if (auto Tickable = Cast<ITickable>(Object))
	{
		TickService->RegisterTick(Tickable);
	}
}

void UBaseFactory::CastModulable(UObject* Object)
{
	if (auto Fragmentable = Cast<IFragmentable>(Object))
	{
		Fragmentable->BuildFragments(FragmentsFactory);
	}
}
