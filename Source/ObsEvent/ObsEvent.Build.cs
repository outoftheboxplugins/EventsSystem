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

            PrivateIncludePaths.AddRange(
            new string[] {
                "Editor/BlueprintGraph/Private",
                "Editor/KismetCompiler/Public",
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

            CircularlyReferencedDependentModules.AddRange(
                new string[] {
                "KismetCompiler",
                "UnrealEd",
                "GraphEditor",
                "Kismet",
                }
            );

            PrivateIncludePaths.AddRange(
            new string[] {
                "Editor/GraphEditor/Private",
                "Editor/Kismet/Private",
                "Editor/AIGraph/Private",
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
