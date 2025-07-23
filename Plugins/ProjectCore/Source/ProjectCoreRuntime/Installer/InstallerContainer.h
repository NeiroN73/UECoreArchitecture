// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProjectCoreRuntime/TableConfigs/Base/TableData.h"
#include "InstallerContainer.generated.h"

UCLASS()
class PROJECTCORERUNTIME_API UInstallerContainer : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<TObjectPtr<UClass>, TObjectPtr<UObject>> Registrations;

	UPROPERTY()
	TMap<FName, TObjectPtr<UDataTable>> DataTableRegistrations;
	
public:
	void Register(UObject* Object);
	
	template<typename T = UObject>
	void Register()
	{
		TSubclassOf<T> InClass = T::StaticClass();
		if (!Registrations.Contains(InClass)) 
		{
			T* Object = NewObject<T>();
			Registrations.Add(InClass, Object);
		}
	}

	template<typename T = UObject>
	T* Resolve()
	{
		TSubclassOf<UObject> InClass = T::StaticClass();
		auto Class = InClass.Get();
		if (auto Object = Registrations.Find(Class))
		{
			return Cast<T>(*Object);
		}
		
		return nullptr;
	}

	void RegisterTableConfig(UDataTable* DataTable)
	{
		auto Name = DataTable->RowStruct->GetFName();
		if (!DataTableRegistrations.Contains(Name))
		{
			DataTableRegistrations.Add(Name, DataTable);
		}
	}
	
	template<typename T = FTableData>
	UDataTable* ResolveTableConfig()
	{
		auto Name = T::StaticStruct()->GetFName();
		if (auto Object = DataTableRegistrations.FindRef(Name))
		{
			return Object;
		}
		
		return nullptr;
	}
	
	template<typename T = UObject>
	TArray<T*> ResolveAll()
	{
		TSubclassOf<UObject> InClass = T::StaticClass();
		TArray<T*> ResultArray;

		for (const auto& Pair : Registrations)
		{
			if (UObject* Object = Pair.Value)
			{
				if (Object->IsA(InClass))
				{
					ResultArray.Add(Cast<T>(Object));
				}
			}
		}
		return ResultArray;
	}

	template<typename TInterface = IInterface>
	TArray<TInterface*> ResolveAllImplements()
	{
		TArray<TInterface*> ResultArray;
		const UClass* InterfaceClass = TInterface::UClassType::StaticClass();
		
		for (const auto& [Class, Object] : Registrations)
		{
			if (Object && Class && Class->ImplementsInterface(InterfaceClass))
			{
				ResultArray.Add(Cast<TInterface>(Object));
			}
		}
		return ResultArray;
	}
};
