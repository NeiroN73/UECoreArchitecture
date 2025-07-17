// Copyright Floruit, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class UHistoryElement;
class UHistoryGraphNode;

class VEILOFFAITHEDITOR_API FHistoryDetailsCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	void RefreshDetails();

	UHistoryGraphNode* GraphNode = nullptr;
	IDetailLayoutBuilder* DetailLayoutBuilder = nullptr;
	UHistoryElement* HistoryElement = nullptr;
};
