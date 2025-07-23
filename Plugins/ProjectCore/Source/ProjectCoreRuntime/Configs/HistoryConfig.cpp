// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryConfig.h"

#include "ProjectCoreRuntime/History/Elements/RootHistoryElement.h"

void UHistoryConfig::Initialize()
{
	Elements = RootHistoryElement->Elements;
}
