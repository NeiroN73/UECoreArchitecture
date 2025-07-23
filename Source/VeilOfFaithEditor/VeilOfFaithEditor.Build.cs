// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VeilOfFaithEditor : ModuleRules
{
	public VeilOfFaithEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", 
		"InputCore", "EnhancedInput", "UMG", "AssetRegistry"
		});

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				// Core modules
				"Engine",
				"CoreUObject",
				"Projects", // IPluginManager
				"UnrealEd", // for FAssetEditorManager
				"RenderCore",
				"InputCore",
				"SlateCore",
				"Slate",
				"EditorStyle",
				"MessageLog",
				"EditorWidgets",
				"WorkspaceMenuStructure",
				"DetailCustomizations",
				"PropertyEditor",
				"BlueprintGraph",
				"Kismet",
				"KismetCompiler",
				"KismetWidgets",
				"GraphEditor",
				"ContentBrowser",
				"ApplicationCore",
				"EditorFramework",
				"VeilOfFaith"
			});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
