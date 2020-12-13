// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

/**
 * Implements the EventsSystem runtime module.
 */

class FEventsSystemModule : public IModuleInterface
{
//IModuleInterface interface
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FEventsSystemModule, EventsSystem);
