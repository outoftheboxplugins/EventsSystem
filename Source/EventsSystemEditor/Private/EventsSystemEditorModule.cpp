// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "EventsSystemEditorModule.h"

#include "ESLog.h"

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
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	AssetActions = MakeShareable(new FESActions);
	AssetTools.RegisterAssetTypeActions(AssetActions.ToSharedRef());
}

void FEventsSystemEditorModule::UnregisterAssetTools()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(AssetActions.ToSharedRef());
	}
}
