// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VeilOfFaithEditorTarget : TargetRules
{
	public VeilOfFaithEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("VeilOfFaith");
		ExtraModuleNames.Add("VeilOfFaithEditor");
	}
}
