// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"

class FESActions;

/**
 * Implements the EventsSystem editor module.
 */

class FEventsSystemEditorModule : public IModuleInterface
{
// IModuleInterface interface
private:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FESActions> AssetActions;
};

IMPLEMENT_MODULE(FEventsSystemEditorModule, EventsSystemEditor);