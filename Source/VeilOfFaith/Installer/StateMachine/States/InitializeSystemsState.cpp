// Copyright Floruit, Inc. All Rights Reserved.


#include "InitializeSystemsState.h"

#include "Engine/StreamableManager.h"
#include "VeilOfFaith/Configs/Base/Configs.h"
#include "VeilOfFaith/Installer/InstallerContainer.h"
#include "VeilOfFaith/Installer/StateMachine/InstallerStateMachine.h"
#include "VeilOfFaith/Factories/HandlersFactory.h"
#include "VeilOfFaith/Factories/FragmentsFactory.h"
#include "VeilOfFaith/Factories/PoolsFactory.h"
#include "VeilOfFaith/Factories/ViewModelsFactory.h"
#include "VeilOfFaith/Factories/ScreensFactory.h"
#include "VeilOfFaith/Factories/ViewsFactory.h"
#include "VeilOfFaith/Services/AssetsLoader.h"
#include "VeilOfFaith/Services/DialoguesService.h"
#include "VeilOfFaith/Services/HistoryService.h"
#include "VeilOfFaith/Services/InvestigationService.h"
#include "VeilOfFaith/Services/LevelsService.h"
#include "VeilOfFaith/Services/TickService.h"
#include "VeilOfFaith/Services/SavingService.h"
#include "VeilOfFaith/Services/ScreensService.h"
#include "VeilOfFaith/SaveStates/HistorySaveState.h"
#include "VeilOfFaith/Services/PreloadsService.h"

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
	Register<UInvestigationService>();
	Register<UDialoguesService>();
	Register<UHandlersService>();
	Register<UHistoryService>();
	Register<UPreloadsService>();
}

void UInitializeSystemsState::InitializeSystems()
{
	Container = StateMachine->InstallerContainer;
	
	Injectables = Container->ResolveAllImplements<IInjectable>();
	Initializables = Container->ResolveAllImplements<IInitializable>();
	Tickables = Container->ResolveAllImplements<ITickable>();
	Fragmentables = Container->ResolveAllImplements<IFragmentable>();

	for (auto Injectable : Injectables)
	{
		Injectable->Inject(Container);
	}

	auto ModuleFactory = Container->Resolve<UFragmentsFactory>();
	for (auto Modulable : Fragmentables)
	{
		Modulable->BuildFragments(ModuleFactory);
	}
	
	for (auto Initializable : Initializables)
	{
		Initializable->Initialize();
	}

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