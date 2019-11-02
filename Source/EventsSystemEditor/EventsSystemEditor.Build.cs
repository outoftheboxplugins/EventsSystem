// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EventsSystemEditor : ModuleRules
{
    public EventsSystemEditor( ReadOnlyTargetRules Target ) : base( Target )
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
                "AssetTools",
                "MainFrame",
			} );

        PrivateIncludePaths.AddRange(
            new string[] {
                "EventsSystemEditor/Private",
                "EventsSystemEditor/Private/AssetTools",
                "EventsSystemEditor/Private/Factories",
                "EventsSystemEditor/Private/Shared",
                "EventsSystemEditor/Private/Styles",
                "EventsSystemEditor/Private/Toolkits",
                "EventsSystemEditor/Private/Widgets",
                "EventsSystemEditor/Private/Nodes"
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
                "EventsSystem",
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