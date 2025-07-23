using UnrealBuildTool;

public class ProjectCoreRuntime : ModuleRules
{
    public ProjectCoreRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "EnhancedInput",
                "UMG",
                "InputCore"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Slate",
                "SlateCore",
                "DlgSystem",
                "MessageLog",
                "UnrealEd"
            }
        );
    }
}