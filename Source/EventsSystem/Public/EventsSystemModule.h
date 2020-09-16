// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"

EVENTSSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogEventsSystem, Log, All);

/**
 * Implements the EventsSystem runtime module.
 */

class FEventsSystemModule : public IModuleInterface
{
// IModuleInterface interface
public:
	virtual bool SupportsDynamicReloading() override { return true; }
};
