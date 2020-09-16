// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "UObject/Interface.h"

#include "ESListenerInterface.generated.h"

// Delegates to implement functionality inside the listener when the event is called.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventCalled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventsSystemPayloadCalled, const UESPayload*, Payload);

// Forward declaration Events System Elements
class UESPayload;
class UESEvent;

UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class UESListenerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Base class for all the listeners across BP types (actors, widgets, components).
 */
class IESListenerInterface
{
	GENERATED_BODY()

// Abstract interface to be implemented by derived classes.
public:
	// Sends the invoke to the delegate of the event.
	virtual void OnEventCalled(const UESPayload* payload) const;

// Public BP API
public:
	// Adds the current listener to the event's listeners.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem")
	virtual void RegisterListener(UESEvent* Event) const;

	// Removes the current listener from the event's listeners.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem")
	virtual void UnregisterListener(UESEvent* Event) const;

// Debugging
public:
	virtual FString GetListenerName() const { return FString("NOT_IMPLEMENTED"); }
};