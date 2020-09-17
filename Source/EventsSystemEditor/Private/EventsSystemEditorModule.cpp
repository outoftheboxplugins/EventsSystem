// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "EventsSystemEditorModule.h"

IMPLEMENT_MODULE(FEventsSystemEditorModule, EventsSystemEditor);
















void FEventsSystemEditorModule::StartupModule()
{
	Style = MakeShareable(new FEventsSystemEditorStyle());

	RegisterAssetTools();
}

void FEventsSystemEditorModule::ShutdownModule()
{
	UnregisterAssetTools();
}

void FEventsSystemEditorModule::RegisterAssetTools()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FEventsSystemActions(Style.ToSharedRef())));
}

void FEventsSystemEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetTypeActions.Add(Action);
}

void FEventsSystemEditorModule::UnregisterAssetTools()
{
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();

		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
}
