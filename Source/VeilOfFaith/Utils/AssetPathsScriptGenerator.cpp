#include "AssetPathsScriptGenerator.h"

void FAssetPathsScriptGenerator::GenerateScriptAssetPaths()
{
    UE_LOG(LogTemp, Warning, TEXT("Generate"));

    FString ClassContent;
    ClassContent.Append("// Script generated!\n\n");
    ClassContent.Append("#pragma once\n\n");
    ClassContent.Append("#include \"AssetPaths.generated.h\"\n\n");
    ClassContent.Append("UCLASS()\n\n");
    ClassContent.Append("class VEILOFFAITH_API UAssetPaths : public UObject\n");
    ClassContent.Append("{\n");
    ClassContent.Append("    GENERATED_BODY()\n\n");

    // Путь к папке, которую вы хотите перебрать
    FString DirectoryPath = FPaths::ProjectContentDir() / TEXT("Game/Resources");
    TArray<FString> FilePaths;
    TArray<FString> DirectoryPaths;

    // Получаем все файлы и папки в указанной директории
    IFileManager& FileManager = IFileManager::Get();
    FileManager.FindFilesRecursive(FilePaths, *DirectoryPath, TEXT("*.*"), true, false);
    FileManager.FindFilesRecursive(DirectoryPaths, *DirectoryPath, TEXT("*"), false, true);

    // Создаем классы для каждой папки
    for (const FString& DirPath : DirectoryPaths)
    {
        // Получаем имя папки
        FString FolderName = FPaths::GetBaseFilename(DirPath);
        
        ClassContent.Append(TEXT("public:\n"));
        ClassContent.Append(FString::Printf(TEXT("    class VEILOFFAITH_API %s\n"), *FolderName));
        ClassContent.Append(TEXT("    {\n"));
        ClassContent.Append(TEXT("    public:\n"));
        
        // Добавляем переменные для файлов в этой папке
        for (const FString& FilePath : FilePaths)
        {
            if (FPaths::GetPath(FilePath) == DirPath)
            {
                // Получаем имя файла без расширения
                FString FileName = FPaths::GetBaseFilename(FilePath);
                
                // Создаем строку для переменной
                ClassContent.Append(FString::Printf(TEXT("        inline const static FString %s = TEXT(\"%s\");\n"), *FileName, *FilePath));
            }
        }
        
        ClassContent.Append(TEXT("    };\n\n"));
    }

    ClassContent.Append("};\n");

    FString FilePath = FPaths::ProjectDir() / TEXT("Source/VeilOfFaith/ScriptsGeneration/AssetPaths.h");
    FFileHelper::SaveStringToFile(ClassContent, *FilePath);

    UE_LOG(LogTemp, Warning, TEXT("Generate %s"), *FilePath);
}
