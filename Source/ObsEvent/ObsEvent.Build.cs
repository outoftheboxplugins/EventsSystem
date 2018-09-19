// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class ObsEvent : ModuleRules
	{
		public ObsEvent(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
                    "Engine"
				});

			PrivateIncludePaths.AddRange(
				new string[] {
					"Runtime/ObsEvent/Private",
				});
		}
	}
}
