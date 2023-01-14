// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

#include "Modules/ModuleManager.h"

/**
 * Implements the EventsSystem editor module.
 */

class FEventsSystemEditorModule : public IModuleInterface
{
// IModuleInterface interface
private:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

// Register & Unregister
private:
	void RegisterAssetTools();
	void UnregisterAssetTools();

private:
	TSharedPtr<class FESActions> AssetActions;
};

IMPLEMENT_MODULE(FEventsSystemEditorModule, EventsSystemEditor);