// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

EVENTSSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogEventsSystem, Log, All);

/**
 * Implements the EventsSystem module.
 */
class FEventsSystemModule
	: public IModuleInterface
{
public:

	//~ IModuleInterface interface

	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }

	virtual bool SupportsDynamicReloading() override
	{
		return true;
	}
};
