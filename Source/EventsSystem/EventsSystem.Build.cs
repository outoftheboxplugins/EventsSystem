// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
namespace UnrealBuildTool.Rules
{
    public class EventsSystem : ModuleRules
    {
        public EventsSystem (ReadOnlyTargetRules Target) : base( Target )
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "UMG"
                } );
        }
    }
}
