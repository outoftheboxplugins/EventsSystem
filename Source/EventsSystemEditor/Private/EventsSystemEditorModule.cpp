// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "EventsSystemEditorModule.h"

IMPLEMENT_MODULE(FEventsSystemEditorModule, EventsSystemEditor);
















void FEventsSystemEditorModule::StartupModule()
{
	Style = MakeShareable(new FEventsSystemEditorStyle());

	RegisterAssetTools();
	RegisterMenuExtensions();
}

void FEventsSystemEditorModule::ShutdownModule()
{
	UnregisterAssetTools();
	UnregisterMenuExtensions();
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

void FEventsSystemEditorModule::RegisterMenuExtensions()
{
	MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
	ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);
}

void FEventsSystemEditorModule::UnregisterMenuExtensions()
{
	MenuExtensibilityManager.Reset();
	ToolBarExtensibilityManager.Reset();
}
