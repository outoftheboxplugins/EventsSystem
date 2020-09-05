// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "Math/NumericLimits.h"

#include "Event.generated.h"

class IEventListenerInterface;
class UEventsSystemPayload;

class AActor;
class UUserWidget;

/**
 * Event holding all the listeners and delegating the call to them.
 */

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "EventsSystem", Blueprintable)
class EVENTSSYSTEM_API UEvent : public UObject
{
	GENERATED_BODY()
	
// Public BP API
public:
	// Invoke the event.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
	static void Invoke(UEvent* EventToInvoke, UEventsSystemPayload* Payload);

	// Invoke the event on a single actor.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
	static void InvokeOnActor(UEvent* EventToInvoke, UEventsSystemPayload* Payload, AActor* Actor);

	// Invoke the event on every actor within a range
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
	static void InvokeOnActorsInRadius(UEvent* EventToInvoke, UEventsSystemPayload* Payload, FVector Origin, float Radius = 100.0f);

    // Invoke the event on a single widget.
    UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
    static void InvokeOnWidget(UUserWidget* Widget, UEvent* EventToInvoke, UEventsSystemPayload* Payload);

// Listeners management
public:
	// Removes all the listeners from one event.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem")
	static void UnRegisterAllListeners(UEvent* EventToClear);

	// Register the listener to the event.
	void RegisterListener(const IEventListenerInterface* Listener);

	// Unregister the listener from the event.
	void UnRegisterListener(const IEventListenerInterface* Listener);

// Editor & Debugging
public:
	// Allows the event to write logs.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EventsSystem|Debug")
	bool bWriteLogs;

	// Short description so you won't forget.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EventsSystem|Debug")
	FText Description;

#ifdef UE_BUILD_DEBUG || UE_EDITOR
public:
	// Invokes the event for debug purposes.
	void DebugInvoke();
#endif

// Internal functionality
private:
	// Delegate the call to the listeners.
	void CallListeners(UEventsSystemPayload* Payload);

	// Delegate the call to all the listeners in rage.
	void CallListenersInRange(UEventsSystemPayload* Payload, FVector Origin, float Range);

	// Delegate the call to all the components listeners on the target actor
	void CallListenerComponents(UEventsSystemPayload* Payload, AActor* Actor);

    // Delegate the call to all the widget listeners on the target widget
    void CallListenerWidget(UUserWidget* Widget, UEventsSystemPayload* Payload);

// Internal state
private:
	// Listeners registered.
	TSet<const IEventListenerInterface*> ActiveListeners;
};
