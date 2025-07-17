#include "CustomIdPropertyTypeCustomization.h"
#include "DetailWidgetRow.h"
#include "IdsConfig.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "VeilOfFaith/EditorUtils/CustomId.h"
#include "DetailLayoutBuilder.h"
#include "IDetailChildrenBuilder.h"
#include "VeilOfFaithEditor/Logger/Logger.h"

TSharedRef<IPropertyTypeCustomization> FCustomIdPropertyTypeCustomization::MakeInstance()
{
    return MakeShareable(new FCustomIdPropertyTypeCustomization);
}

void FCustomIdPropertyTypeCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
    FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    IdNameHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCustomId, IdName));

    if (!IdNameHandle.IsValid())
        return;

    Ids = GetIds();

    HeaderRow
        .NameContent()
        [
            PropertyHandle->CreatePropertyNameWidget()
        ]
        .ValueContent()
        .MinDesiredWidth(250.f)
        [
            SNew(SComboBox<FName>)
            .OptionsSource(&Ids)
            .OnGenerateWidget_Lambda([](FName Item) -> TSharedRef<SWidget>
            {
                return SNew(STextBlock).Text(FText::FromName(Item));
            })
            .OnSelectionChanged_Lambda([this](FName NewValue, ESelectInfo::Type)
            {
                IdNameHandle->SetValue(NewValue);
            })
            .Content()
            [
                SNew(STextBlock)
                .Text_Lambda([this]
                {
                    FName CurrentValue;
                    IdNameHandle->GetValue(CurrentValue);
                    return FText::FromName(CurrentValue);
                })
            ]
        ];
}

void FCustomIdPropertyTypeCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle,
    IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
    AddedIdNameHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCustomId, AddedIdName));
    RemovedIdNameHandle = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCustomId, RemovedIdName));
    TSharedPtr<SComboBox<FName>> RemoveIdComboBox;
    
    ChildBuilder.AddCustomRow(FText::FromString("ID Management"))
    [
        SNew(SVerticalBox)
        
        // Заголовок раздела
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(0, 5)
        [
            SNew(STextBlock)
            .Text(FText::FromString("ID Editor"))
            .Font(IDetailLayoutBuilder::GetDetailFontBold())
        ]
        
        // Добавление нового ID
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(0, 5)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(0, 0, 5, 0)
            [
                SNew(STextBlock)
                .Text(FText::FromString("Add:"))
            ]
            + SHorizontalBox::Slot()
            .FillWidth(1.0f)
            [
                SNew(SEditableTextBox)
                .HintText(FText::FromString("New ID"))
                .OnTextCommitted_Lambda([this](const FText& Text, ETextCommit::Type CommitType)
                {
                    if (CommitType == ETextCommit::OnEnter)
                    {
                        AddId(FName(Text.ToString()));
                    }
                })
            ]
        ]
        
        // Удаление существующего ID
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(0, 5)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(0, 0, 5, 0)
            [
                SNew(STextBlock)
                .Text(FText::FromString("Remove:"))
            ]
            + SHorizontalBox::Slot()
            .FillWidth(1.0f)
            [
                SNew(SComboBox<FName>)
                .OptionsSource(&GetIds())
                .OnGenerateWidget_Lambda([](FName Item) -> TSharedRef<SWidget>
                {
                    return SNew(STextBlock).Text(FText::FromName(Item));
                })
                .OnSelectionChanged_Lambda([this](FName ValueToRemove, ESelectInfo::Type SelectInfo)
                {
                    RemoveId(ValueToRemove);
                })
                .Content()
                [
                    SNew(STextBlock)
                    .Text(FText::FromString("Select ID"))
                ]
            ]
        ]
    ];
}

TArray<FName>& FCustomIdPropertyTypeCustomization::GetIds()
{
    if (auto IdsConfig = GetIdsConfig())
    {
        Ids = IdsConfig->Ids;
    }
    
    return Ids;
}

UIdsConfig* FCustomIdPropertyTypeCustomization::GetIdsConfig()
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    TArray<FAssetData> Assets;
    AssetRegistryModule.Get().GetAssetsByClass(UIdsConfig::StaticClass()->GetClassPathName(), Assets);

    return Assets.Num() > 0 ? Cast<UIdsConfig>(Assets[0].GetAsset()) : nullptr;
}

void FCustomIdPropertyTypeCustomization::AddId(FName InId)
{
    if (auto IdsConfig = GetIdsConfig())
    {
        if (!IdsConfig->Ids.Contains(InId))
        {
            IdsConfig->Ids.Add(InId);
            Ids = IdsConfig->Ids;
            IdNameHandle->SetValue(InId);
            AddedIdNameHandle->SetValue(NAME_None);
            
            IdsConfig->MarkPackageDirty();
            IdsConfig->SaveConfig(CPF_Config, *IdsConfig->GetPathName());

            FLogger::ShowNotification(FString::Printf(TEXT("Id %s added!"), *InId.ToString()));
        }
    }
}

void FCustomIdPropertyTypeCustomization::RemoveId(FName InId)
{
    if (auto IdsConfig = GetIdsConfig())
    {
        if (IdsConfig->Ids.Contains(InId))
        {
            FName CurrentId;
            if (IdNameHandle.IsValid())
            {
                IdNameHandle->GetValue(CurrentId);
                RemovedIdNameHandle->SetValue(NAME_None);
                bool bWasCurrentId = (CurrentId == InId);
                
                if (bWasCurrentId)
                {
                    IdNameHandle->SetValue(NAME_None);
                }

                IdsConfig->Ids.Remove(InId);
                Ids = IdsConfig->Ids;

                FLogger::ShowNotification(FString::Printf(TEXT("Id %s removed!"), *InId.ToString()));
            }
            
            IdsConfig->MarkPackageDirty();
            IdsConfig->SaveConfig(CPF_Config, *IdsConfig->GetPathName());
        }
    }
}