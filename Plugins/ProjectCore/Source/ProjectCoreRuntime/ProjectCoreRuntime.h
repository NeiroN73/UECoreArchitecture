#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FProjectCoreRuntimeModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
