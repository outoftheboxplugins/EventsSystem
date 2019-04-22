// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

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
                "InputCore",
                "Slate",
                "EditorStyle",
                "UMG"
            }
        );

            PrivateDependencyModuleNames.AddRange(
            new string[] {
                "EditorStyle",
                "KismetCompiler",
                "UnrealEd",
                "GraphEditor",
                "SlateCore",
                "Kismet",
                "KismetWidgets",
                "PropertyEditor",
            }
        );

            PrivateIncludePathModuleNames.AddRange(
                new string[] {
                "AssetRegistry",
                "AssetTools",
                "ContentBrowser"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                "Core",
                "CoreUObject",
                "ApplicationCore",
                "Engine",
                "RenderCore",
                "InputCore",
                "Slate",
                "SlateCore",
                "EditorStyle",
                "UnrealEd",
                "MessageLog",
                "GraphEditor",
                "Kismet",
                "AnimGraph",
                "BlueprintGraph",
                "AIModule",
                "ClassViewer"
                }
            );

            DynamicallyLoadedModuleNames.AddRange(
                new string[] {
                "AssetTools",
                "AssetRegistry",
                "ContentBrowser"
                }
            );
        }
	}
}
