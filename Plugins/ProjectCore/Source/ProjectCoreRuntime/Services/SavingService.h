// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Base/Service.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/Installer/Initializable.h"
#include "ProjectCoreRuntime/Installer/Injectable.h"
#include "SavingService.generated.h"

class ISavable;
class USaveGame;

UCLASS()
class PROJECTCORERUNTIME_API USavingService : public UService,
public IInitializable,
public IInjectable
{
	GENERATED_BODY()

public:
	virtual void Inject(TObjectPtr<UInstallerContainer> Container) override;
	virtual void Initialize() override;

	void Save();
	void Load();

private:
	UPROPERTY()
	TArray<TObjectPtr<USaveState>> States;
	
	void OnSaved(const FString& SlotName, int32 UserIndex, bool bSuccess);
	void OnLoaded(const FString& SlotName, int32 UserIndex, USaveGame* SaveGame);
};
