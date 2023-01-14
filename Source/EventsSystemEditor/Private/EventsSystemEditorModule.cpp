// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#include "EventsSystemEditorModule.h"

#include "ESActions.h"
#include "ESLog.h" // for Debugging Logs
#include "AssetToolsModule.h" // for FAssetToolsModule

void FEventsSystemEditorModule::StartupModule()
{
	LOG_TRACE();

	RegisterAssetTools();
}

void FEventsSystemEditorModule::ShutdownModule()
{
	LOG_TRACE();

	UnregisterAssetTools();
}

void FEventsSystemEditorModule::RegisterAssetTools()
{
	if (FAssetToolsModule::IsModuleLoaded())
	{
		IAssetTools& AssetTools = FAssetToolsModule::GetModule().Get();

		AssetActions = MakeShareable(new FESActions);
		AssetTools.RegisterAssetTypeActions(AssetActions.ToSharedRef());
	}
	else
	{
		UE_LOG(LogEventsSystem, Warning, TEXT("FAssetToolsModule not loaded, cannot register asset tools."))
	}
}

void FEventsSystemEditorModule::UnregisterAssetTools()
{
	if (FAssetToolsModule::IsModuleLoaded())
	{
		IAssetTools& AssetTools = FAssetToolsModule::GetModule().Get();
		AssetTools.UnregisterAssetTypeActions(AssetActions.ToSharedRef());
	}
	else
	{
		UE_LOG(LogEventsSystem, Warning, TEXT("FAssetToolsModule not loaded, cannot unregister asset tools."))
	}
}
