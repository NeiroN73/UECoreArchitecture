// Copyright Floruit, Inc. All Rights Reserved.


#include "HandlersScanner.h"

#include "Components/Button.h"

void UHandlersScanner::NativeConstruct()
{
	Super::NativeConstruct();

	if (AssetPathsButton)
	{
		AssetPathsButton->OnClicked.AddDynamic(this, &UHandlersScanner::GenerateScriptIds);
	}
}

void UHandlersScanner::GenerateScriptAssetPaths()
{
	FString ClassContent;
	ClassContent.Append("// Script generated!\n\n");
	ClassContent.Append("#pragma once\n\n");
	ClassContent.Append("#include \"AssetPaths.generated.h\"\n\n");
	ClassContent.Append("UCLASS()\n\n");
	ClassContent.Append("class VEILOFFAITH_API UAssetPaths : public UObject\n");
	ClassContent.Append("{\n");
	ClassContent.Append("    GENERATED_BODY()\n\n");
	ClassContent.Append("public:\n");

	FString DirectoryPath = FPaths::ProjectContentDir() / TEXT("Assets");
	TArray<FString> FilePaths;

	IFileManager& FileManager = IFileManager::Get();
	FileManager.FindFilesRecursive(FilePaths, *DirectoryPath, TEXT("*.*"), true, false);

	for (const FString& FilePath : FilePaths)
	{
		FString FileName = FPaths::GetBaseFilename(FilePath);
		FString RelativePath = FilePath;
		RelativePath.RemoveFromStart(FPaths::ProjectContentDir() + TEXT("/"));
		ClassContent.Append(FString::Printf(TEXT("    inline const static FString %s = TEXT(\"%s\");\n"), *FileName, *RelativePath));
	}

	ClassContent.Append("};\n");

	FString FilePath = FPaths::ProjectDir() / TEXT("Source/VeilOfFaith/ScriptsGeneration/AssetPaths.h");
	FFileHelper::SaveStringToFile(ClassContent, *FilePath);
}

void UHandlersScanner::GenerateScriptIds()
{
    FString ClassContent;
	ClassContent.Append("// Copyright Floruit, Inc. All Rights Reserved.\n\n");
    ClassContent.Append("// Script generated!\n\n");
    ClassContent.Append("#pragma once\n\n");
    ClassContent.Append("#include \"CoreMinimal.h\"\n");
    ClassContent.Append("class VEILOFFAITH_API Ids\n");
    ClassContent.Append("{\n");
    ClassContent.Append("public:\n");

    FString RootDirectoryPath = FPaths::ProjectContentDir() / TEXT("Assets");
    TArray<FString> FilePaths;

    IFileManager& FileManager = IFileManager::Get();
    FileManager.FindFilesRecursive(FilePaths, *RootDirectoryPath, TEXT("*.*"), true, false);

    // Карты для хранения данных
    TMap<FString, TArray<FString>> FolderToFilesMap;
    TMap<FString, int32> FileNameUsageCount;
    TMap<FString, int32> FolderListNameUsageCount;

    for (const FString& FilePath : FilePaths)
    {
        FString RelativePath = FilePath;
        RelativePath.RemoveFromStart(FPaths::ProjectContentDir() + TEXT("/"));
        
        // Получаем путь к папке относительно Assets
        FString FolderPath = FPaths::GetPath(RelativePath);
        FolderPath.RemoveFromStart(TEXT("Assets/"));
        
        // Обработка имени файла
        FString FileName = FPaths::GetBaseFilename(FilePath);
        FString CleanName = FileName;
        
        // Удаляем префиксы/постфиксы
        CleanName.RemoveFromStart("SM_");
        CleanName.RemoveFromStart("T_");
        CleanName.RemoveFromStart("BP_");
        CleanName.RemoveFromStart("D_");
        CleanName.RemoveFromEnd("_D");
        CleanName.RemoveFromEnd("_C");
        
        // Добавляем подчеркивания для camelCase
        FString ResultName;
        for (int32 i = 0; i < CleanName.Len(); ++i)
        {
            if (i > 0 && FChar::IsUpper(CleanName[i]))
            {
                ResultName += TEXT("_");
            }
            ResultName += FChar::ToLower(CleanName[i]);
        }
        
        // Заменяем специальные символы
        ResultName = ResultName.Replace(TEXT(" "), TEXT("_"))
                             .Replace(TEXT("-"), TEXT("_"))
                             .Replace(TEXT("."), TEXT("_"))
                             .Replace(TEXT("__"), TEXT("_"));

        // Обрабатываем дубликаты имен файлов
        if (FileNameUsageCount.Contains(ResultName))
        {
            int32 Index = ++FileNameUsageCount[ResultName];
            ResultName = FString::Printf(TEXT("%s%d"), *ResultName, Index);
        }
        else
        {
            FileNameUsageCount.Add(ResultName, 1);
        }

        // Добавляем в карту
        if (!FolderToFilesMap.Contains(FolderPath))
        {
            FolderToFilesMap.Add(FolderPath, TArray<FString>());
        }
        FolderToFilesMap[FolderPath].Add(ResultName);
    }

    // Генерируем переменные и списки
    for (const auto& Pair : FolderToFilesMap)
    {
        const FString& FolderPath = Pair.Key;
        const TArray<FString>& FileNames = Pair.Value;

        // Формируем имя списка на основе названия папки
        FString FolderListName = FPaths::GetCleanFilename(FolderPath);
        FolderListName = FolderListName + "Assets";

        // Обрабатываем дубликаты имен списков
        if (FolderListNameUsageCount.Contains(FolderListName))
        {
            int32 Index = ++FolderListNameUsageCount[FolderListName];
            FolderListName = FString::Printf(TEXT("%s%d"), *FolderListName, Index);
        }
        else
        {
            FolderListNameUsageCount.Add(FolderListName, 1);
        }

        // Добавляем переменные для каждого файла
        for (const FString& FileName : FileNames)
        {
            ClassContent.Append(FString::Printf(TEXT("    inline const static FName %s = TEXT(\"%s\");\n"), 
                *FileName, *FileName));
        }

        // Добавляем список для папки
        ClassContent.Append(FString::Printf(TEXT("\n    inline const static TArray<FName> %s = {\n"), 
            *FolderListName));

        for (int32 i = 0; i < FileNames.Num(); ++i)
        {
            if (i == FileNames.Num() - 1)
            {
                ClassContent.Append(FString::Printf(TEXT("        %s\n"), *FileNames[i]));
            }
            else
            {
                ClassContent.Append(FString::Printf(TEXT("        %s,\n"), *FileNames[i]));
            }
        }
        ClassContent.Append("    };\n\n");
    }

    // Добавляем общий список всех ассетов
    TArray<FString> AllAssetNames;
    for (const auto& Pair : FolderToFilesMap)
    {
        AllAssetNames.Append(Pair.Value);
    }

    ClassContent.Append("    inline const static TArray<FName> AllAssetNames = {\n");
    for (int32 i = 0; i < AllAssetNames.Num(); ++i)
    {
        if (i == AllAssetNames.Num() - 1)
        {
            ClassContent.Append(FString::Printf(TEXT("        %s\n"), *AllAssetNames[i]));
        }
        else
        {
            ClassContent.Append(FString::Printf(TEXT("        %s,\n"), *AllAssetNames[i]));
        }
    }
    ClassContent.Append("    };\n");

    ClassContent.Append("};\n");

    FString FilePath = FPaths::ProjectDir() / TEXT("Source/VeilOfFaith/ScriptsGeneration/Ids.h");
    FFileHelper::SaveStringToFile(ClassContent, *FilePath);
}
