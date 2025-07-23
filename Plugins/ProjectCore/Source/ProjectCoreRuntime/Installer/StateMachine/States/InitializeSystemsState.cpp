// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeSystemsState.h"

#include "Engine/StreamableManager.h"
#include "ProjectCoreRuntime/Configs/Base/Configs.h"
#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/Installer/StateMachine/InstallerStateMachine.h"
#include "ProjectCoreRuntime/Factories/HandlersFactory.h"
#include "ProjectCoreRuntime/Factories/FragmentsFactory.h"
#include "ProjectCoreRuntime/Factories/PoolsFactory.h"
#include "ProjectCoreRuntime/Factories/ViewModelsFactory.h"
#include "ProjectCoreRuntime/Factories/ScreensFactory.h"
#include "ProjectCoreRuntime/Factories/ViewsFactory.h"
#include "ProjectCoreRuntime/Services/AssetsLoader.h"
#include "ProjectCoreRuntime/Services/HistoryService.h"
#include "ProjectCoreRuntime/Services/LevelsService.h"
#include "ProjectCoreRuntime/Services/TickService.h"
#include "ProjectCoreRuntime/Services/SavingService.h"
#include "ProjectCoreRuntime/Services/ScreensService.h"
#include "ProjectCoreRuntime/SaveStates/HistorySaveState.h"
#include "ProjectCoreRuntime/Services/PreloadsService.h"

void UInitializeSystemsState::Enter()
{
	StateMachine->InstallerContainer = NewObject<UInstallerContainer>();
	Register(StateMachine);
	
	RegisterConfigs();
	RegisterTableConfigs();
	RegisterSaveStates();
	RegisterFactories();
	RegisterServices();

	InitializeSystems();
	
	StateMachine->NextState();
}

void UInitializeSystemsState::RegisterConfigs()
{
	auto Configs = Cast<UConfigs>(StateMachine->LoadedConfigsHandler->GetLoadedAsset())->Configs;
	for (const auto Config : Configs)
	{
		Register(Config);
	}
}

void UInitializeSystemsState::RegisterTableConfigs()
{
	auto TableConfigs =
		Cast<UConfigs>(StateMachine->LoadedConfigsHandler->GetLoadedAsset())->TableConfigs;
	for (auto TableConfig : TableConfigs)
	{
		StateMachine->InstallerContainer->RegisterTableConfig(TableConfig);
	}
}

void UInitializeSystemsState::RegisterSaveStates()
{
	Register<UHistorySaveState>();
}

void UInitializeSystemsState::RegisterFactories()
{
	Register<UViewModelsFactory>();
	Register<UScreensFactory>();
	Register<UHandlersFactory>();
	Register<UPoolsFactory>();
	Register<UFragmentsFactory>();
	Register<UViewsFactory>();
}

void UInitializeSystemsState::RegisterServices()
{
	Register(StateMachine->AssetsLoaderService);
	
	Register<USavingService>();
	Register<UScreensService>();
	Register<ULevelsService>();
	Register<UTickService>();
	Register<UHandlersService>();
	Register<UHistoryService>();
	Register<UPreloadsService>();
}

void UInitializeSystemsState::InitializeSystems()
{
	Container = StateMachine->InstallerContainer;
	
	Injectables = Container->ResolveAllImplements<IInjectable>();
	for (auto Injectable : Injectables)
	{
		Injectable->Inject(Container);
	}

	Fragmentables = Container->ResolveAllImplements<IFragmentable>();
	auto FragmentsFactory = Container->Resolve<UFragmentsFactory>();
	for (auto Fragmentable : Fragmentables)
	{
		Fragmentable->BuildFragments(FragmentsFactory);
	}

	Initializables = Container->ResolveAllImplements<IInitializable>();
	for (auto Initializable : Initializables)
	{
		Initializable->Initialize();
	}

	Tickables = Container->ResolveAllImplements<ITickable>();
	auto TickService = Container->Resolve<UTickService>();
	for (auto Tickable : Tickables)
	{
		TickService->RegisterTick(Tickable);
	}
}

void UInitializeSystemsState::Register(UObject* Object)
{
	StateMachine->InstallerContainer->Register(Object);
}