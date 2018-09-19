// Copyright 2018 pasotee. All Rights Reserved.

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
