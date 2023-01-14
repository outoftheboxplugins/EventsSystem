// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
using UnrealBuildTool;

public class EventsSystemEditor : ModuleRules
{
    public EventsSystemEditor (ReadOnlyTargetRules Target) : base( Target )
    {
        PrivateIncludePaths.AddRange(
            new string[] {
                "EventsSystemEditor/Private",
                "EventsSystemEditor/Private/AssetTools",
                "EventsSystemEditor/Private/Factories",
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
    }
}