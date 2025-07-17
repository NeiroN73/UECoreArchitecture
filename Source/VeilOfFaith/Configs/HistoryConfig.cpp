// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryConfig.h"

#include "VeilOfFaith/History/Elements/RootHistoryElement.h"

void UHistoryConfig::Initialize()
{
	Elements = RootHistoryElement->Elements;
}
