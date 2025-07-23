// Copyright Floruit, Inc. All Rights Reserved.


#include "HistoryCondition.h"

void UHistoryCondition::MarkCompleted()
{
	bCompleted = true;
	OnCompleted.ExecuteIfBound();
}
