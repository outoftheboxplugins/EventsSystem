// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "EventsSystemEditorModule.h"

void FEventsSystemEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	AssetActions = MakeShareable(new FESActions);
	AssetTools.RegisterAssetTypeActions(AssetActions.ToSharedRef());
}

void FEventsSystemEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(AssetActions.ToSharedRef());
	}
}
