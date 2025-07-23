// Copyright Floruit, Inc. All Rights Reserved.


#include "IntTextBinder.h"

#include "Components/TextBlock.h"

void UIntTextBinder::Bind(UTextBlock* TextBlock, const int32& Value)
{
	TextBlock->SetText(FText::AsNumber(Value));
}
