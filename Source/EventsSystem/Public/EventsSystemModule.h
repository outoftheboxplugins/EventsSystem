// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

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
