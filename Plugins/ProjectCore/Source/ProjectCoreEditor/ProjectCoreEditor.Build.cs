using UnrealBuildTool;

public class ProjectCoreEditor : ModuleRules
{
    public ProjectCoreEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core",
            "CoreUObject",
            "Engine", 
            "InputCore",
            "EnhancedInput",
            "UMG",
            "AssetRegistry"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Projects",
            "UnrealEd",        
            "Slate",
            "SlateCore",
            "EditorStyle",      
            "PropertyEditor",   
            "DetailCustomizations",
            "ContentBrowser",   
            "ProjectCoreRuntime",
            "EditorFramework",
            "ApplicationCore"
        });
    }
}