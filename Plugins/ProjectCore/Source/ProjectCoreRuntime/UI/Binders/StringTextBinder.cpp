// Copyright Floruit, Inc. All Rights Reserved.


#include "StringTextBinder.h"

#include "Components/TextBlock.h"

void UStringTextBinder::Bind(UTextBlock* TextBlock, const FString& Value)
{
	TextBlock->SetText(FText::FromString(Value));
}
