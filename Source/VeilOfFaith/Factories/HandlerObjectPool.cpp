// Copyright Floruit, Inc. All Rights Reserved.


#include "HandlerObjectPool.h"

#include "VeilOfFaith/Installer/InstallerContainer.h"

void UHandlerObjectPool::Return(AObjectPoolHandler* Handler)
{
	if (Handler)
	{
		Handler->Return();
	}
}

void UHandlerObjectPool::Release()
{
	for (auto Handler : Pool)
	{
		if (Handler)
		{
			Handler->Return();
			Handler->Destroy();
		}
	}
	Pool.Empty();
	PoolContainer->Destroy();
}

void UHandlerObjectPool::Inject(TObjectPtr<UInstallerContainer> Container)
{
	HandlerFactory = Container->Resolve<UHandlersFactory>();
}