// Copyright Alexandru pasotee Oprea 2018-2019. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "ESPayload.generated.h"

/**
 * Event holding all the listeners and delegating the call to them.
 */

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "EventsSystem", Blueprintable)
class EVENTSSYSTEM_API UESPayload : public UObject
{
	GENERATED_BODY()
};
