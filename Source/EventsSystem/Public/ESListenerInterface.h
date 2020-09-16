// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "ESEvent.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "ESListenerInterface.generated.h"

class UESPayload;

/**
 * Interface for creating Event listeners of any type.
 */
//TODO: Hide more categories on the classes inherited from this.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventCalled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventsSystemPayloadCalled, const UESPayload*, Payload);

class UESEvent;

UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class UESListenerInterface : public UInterface
{
	GENERATED_BODY()
};

class IESListenerInterface
{
	GENERATED_BODY()

public:
	// Adds the current listener to the event's listeners
	UFUNCTION(BlueprintCallable, Category = "EventsSystem")
	virtual void RegisterListener(UESEvent* Event) const;

	// Removes the current listener from the event's listeners
	UFUNCTION(BlueprintCallable, Category = "EventsSystem")
	virtual void UnregisterListener(UESEvent* Event) const;

	// Sends the invoke to the delegate of the event.
	virtual void OnEventCalled(const UESPayload* payload) const {}

	virtual FString GetListenerName() const { return FString("NOT_IMPLEMENTED"); }
};