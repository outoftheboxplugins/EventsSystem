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
                "ContentBrowser",
                "Core",
                "CoreUObject",
                "DesktopWidgets",
                "EditorStyle",
                "Engine",
                "InputCore",
                "Projects",
                "Slate",
                "SlateCore",
                "ObsEvent",
                "UnrealEd",
                "Projects",
                "BlueprintGraph",
                "KismetCompiler",
    } );

            PrivateIncludePathModuleNames.AddRange(
                new string[] {
                "AssetTools",
                "UnrealEd",
                } );
        }
	}
}
