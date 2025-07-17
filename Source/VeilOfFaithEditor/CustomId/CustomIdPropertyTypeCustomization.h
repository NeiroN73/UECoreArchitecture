// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UIdsConfig;

class VEILOFFAITHEDITOR_API FCustomIdPropertyTypeCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
	
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow,
		IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder,
		IPropertyTypeCustomizationUtils& CustomizationUtils) override;

private:
	TArray<FName>& GetIds();
	UIdsConfig* GetIdsConfig();
	void AddId(FName InId);
	void RemoveId(FName InId);
	
	TArray<FName> Ids;

	TSharedPtr<IPropertyHandle> IdNameHandle;
	TSharedPtr<IPropertyHandle> AddedIdNameHandle;
	TSharedPtr<IPropertyHandle> RemovedIdNameHandle;
};
