// Copyright Floruit, Inc. All Rights Reserved.


#include "InvestigationService.h"

#include "ProjectCoreRuntime/Installer/InstallerContainer.h"
#include "ProjectCoreRuntime/TableConfigs/NewsTableData.h"

void UInvestigationService::Inject(TObjectPtr<UInstallerContainer> Container)
{
	DaysTableConfig = Container->ResolveTableConfig<FNewsTableData>();
}

void UInvestigationService::Initialize()
{
	//auto Test = DaysTableConfig->FindRow<>()
}
