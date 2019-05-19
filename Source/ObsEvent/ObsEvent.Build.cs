// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

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
                    "Engine",
                    "UMG"
                });

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd",
                    "BlueprintGraph",
                    "KismetCompiler",
                } );
        }
	}
}
