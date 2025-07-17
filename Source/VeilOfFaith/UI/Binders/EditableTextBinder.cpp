// Copyright Floruit, Inc. All Rights Reserved.


#include "EditableTextBinder.h"

#include "Components/EditableText.h"

void UEditableTextBinder::Bind(TObjectPtr<UEditableText> EditableText)
{
	EditableText->OnTextChanged.AddDynamic(this, &UEditableTextBinder::OnTextChanged);
}

void UEditableTextBinder::OnTextChanged(const FText& Text)
{
	OnBinderTriggered.Execute(Text.ToString());
}
