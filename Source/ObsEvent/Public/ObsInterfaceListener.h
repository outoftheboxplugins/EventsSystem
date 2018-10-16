// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#pragma once

#include "ObsEvent.h"
#include "ObsInterfaceListener.generated.h"

/**
 * Interface for creating Event listeners of any type..
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventCalled);

class UObsEvent;

UINTERFACE(Blueprintable)
class UObsInterfaceListener : public UInterface
{
	GENERATED_BODY()
};

//TODO: Check if we can add and remove them in the interface constructor.

class IObsInterfaceListener
{
	GENERATED_BODY()

public:
	// Adds the current listener to the event's listeners
	virtual void RegisterListener(UObsEvent* ObsEvent) const;

	// Removes the current listener from the event's listeners
	virtual void UnregisterListener(UObsEvent* ObsEvent) const;

	// Callback when the event is invoked.
	virtual void OnEventCalled() const {}
};