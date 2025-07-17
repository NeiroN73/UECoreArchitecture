// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VeilOfFaithTarget : TargetRules
{
	public VeilOfFaithTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("VeilOfFaith");
		ExtraModuleNames.Add("VeilOfFaithEditor");
	}
}
