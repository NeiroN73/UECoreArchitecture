// Copyright Floruit, Inc. All Rights Reserved.


#include "NameTextBinder.h"

#include "Components/TextBlock.h"

void UNameTextBinder::Bind(UTextBlock* TextBlock, const FName& Value)
{
	TextBlock->SetText(FText::FromName(Value));
}
