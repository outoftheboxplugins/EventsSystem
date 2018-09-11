// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EventSystemEditor : ModuleRules
{
	public EventSystemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
            );
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
                "EventSystemEditor/Private",
                "EventSystemEditor/Private/Factories",
                "EventSystemEditor/Private/AssetTools"
				// ... add other private include paths required here ...
			}
            );
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
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
                "EventSystem",
                "UnrealEd",

				// ... add private dependencies that you statically link with here ...	
			}
            );
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
                "AssetTools",
                "MainFrame",
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
