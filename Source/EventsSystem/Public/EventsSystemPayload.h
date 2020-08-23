// Copyright Alexandru pasotee Oprea 2018-2019. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "EventsSystemPayload.generated.h"

/**
 * Event holding all the listeners and delegating the call to them.
 */

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "EventsSystem", Blueprintable)
class Event_API UEventsSystemPayload : public UObject
{
	GENERATED_BODY()
};
