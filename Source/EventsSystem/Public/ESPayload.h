// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

#include "ESPayload.generated.h"

/**
 * Base class for all the BP Payloads created for events.
 */

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = EventsSystem, Category = "EventsSystem", Blueprintable)
class EVENTSSYSTEM_API UESPayload : public UObject
{
	GENERATED_BODY()
};
