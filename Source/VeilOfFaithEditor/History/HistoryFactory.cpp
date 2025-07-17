// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryFactory.h"

#include "VeilOfFaith/History/Elements/RootHistoryElement.h"
#include "VeilOfFaith/History/Elements/HistoryElement.h"


UHistoryFactory::UHistoryFactory(const FObjectInitializer& ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = URootHistoryElement::StaticClass();
}

UObject* UHistoryFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<URootHistoryElement>(InParent, InClass, InName, Flags | RF_Transactional);
}
