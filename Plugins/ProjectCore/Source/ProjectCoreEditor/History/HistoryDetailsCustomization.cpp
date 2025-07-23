// Copyright Floruit, Inc. All Rights Reserved.

#include "HistoryDetailsCustomization.h"
#include "DetailLayoutBuilder.h"

TSharedRef<IDetailCustomization> FHistoryDetailsCustomization::MakeInstance()
{
    return MakeShareable(new FHistoryDetailsCustomization);
}

void FHistoryDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
 //     DetailBuilder.HideCategory("Advanced");
 //     DetailBuilder.HideCategory("Object");
 //    
 //     IDetailCategoryBuilder& MainCategory = DetailBuilder.EditCategory("Main");
 //    
 //    MainCategory.AddProperty(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UReferencedHistoryGraphNode, Element)));
	// MainCategory.AddProperty(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UInstancedHistoryGraphNode, Element)));
	//
 //     MainCategory.AddProperty(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UHistoryElement, Id)));
 //     MainCategory.AddProperty(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UHistoryElement, bOnlyFirstConditionComplete)));
 //    
 //     MainCategory.AddProperty(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UHistoryElement, Triggers)));
 //     MainCategory.AddProperty(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UHistoryElement, Actions)));
 //     MainCategory.AddProperty(DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UHistoryElement, Conditions)));
 //
	// IDetailCategoryBuilder& BaseDataCategory = DetailLayoutBuilder->EditCategory(TEXT("Base Node"), FText::GetEmpty(), ECategoryPriority::Important);
	// BaseDataCategory.InitiallyCollapsed(false);
	// const TSharedPtr<IPropertyHandle> PropertyDialogueNode =
	// 	DetailLayoutBuilder->GetProperty(UDialogueGraphNode::GetMemberNameDialogueNode(), UDialogueGraphNode::StaticClass());

    
    // TSharedRef<IPropertyHandle> ElementHandle = DetailBuilder.GetProperty(
    //     GET_MEMBER_NAME_CHECKED(UReferencedHistoryGraphNode, Element)
    // );
    //
    // TSharedRef<IPropertyHandle> NestedIdHandle = ElementHandle->GetChildHandle("Id").ToSharedRef();
    // MainCategory.AddProperty(NestedIdHandle);

 //    DetailLayoutBuilder = &DetailBuilder;
 //    
 //    TSharedRef<IPropertyHandle> ElementHandle = DetailBuilder.GetProperty(
 //        GET_MEMBER_NAME_CHECKED(UReferencedHistoryGraphNode, Element)
 //    );
 //    
 //    TSharedRef<IPropertyHandle> ElementHandleId = DetailBuilder.GetProperty(
 //        GET_MEMBER_NAME_CHECKED(UHistoryElement, Id), FCustomId::StaticStruct());
 //    
 //    ElementHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateSP(
 //        this, &FHistoryDetailsCustomization::RefreshDetails
 //    ));
 //    
 //    MainCategory.AddProperty(ElementHandle);
 //    MainCategory.AddProperty(ElementHandleId);
 //
 //    FText CustomTextValue;
 //    
 //    MainCategory.AddCustomRow(FText::FromString("Test Filter"), true)
 // .NameContent()
 // [
 //     SNew(STextBlock)
 //     .Text(FText::FromString("Custom Property"))
 //     .Font(IDetailLayoutBuilder::GetDetailFont())
 // ]
 // .ValueContent()
 // [
 //     SNew(SEditableTextBox)
 //     .Text(TAttribute<FText>::Create([this, CustomTextValue]() { return CustomTextValue; }))
 //     .Font(IDetailLayoutBuilder::GetDetailFont())
 // ];
 //    
 //    RefreshDetails();
}

void FHistoryDetailsCustomization::RefreshDetails()
{
    if (!DetailLayoutBuilder) return;
    
    IDetailLayoutBuilder& DetailBuilder = *DetailLayoutBuilder;
    DetailBuilder.ForceRefreshDetails();
}