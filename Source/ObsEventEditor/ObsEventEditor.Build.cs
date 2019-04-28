// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ObsEventEditor : ModuleRules
{
	public ObsEventEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"MainFrame",
			});

		PrivateIncludePaths.AddRange(
			new string[] {
				"ObsEventEditor/Private",
				"ObsEventEditor/Private/AssetTools",
				"ObsEventEditor/Private/Factories",
				"ObsEventEditor/Private/Shared",
				"ObsEventEditor/Private/Styles",
				"ObsEventEditor/Private/Toolkits",
				"ObsEventEditor/Private/Widgets",
                "ObsEventEditor/Private/Nodes",
            } );

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
			});
	}
}
