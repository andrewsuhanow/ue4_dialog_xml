// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XML : ModuleRules
{
	public XML(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
                                                            "PugiXML_Plagin"});
	}
}
