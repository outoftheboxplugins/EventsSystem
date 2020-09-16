// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "UObject/Object.h"

#include "ESEvent.generated.h"

// Forward declaration UE types
class AActor;
class UUserWidget;

// Forward declaration Events System Elements
class IESListenerInterface;
class UESPayload;

/**
 * Event holding all the listeners and delegating the call to them.
 */

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "EventsSystem", Blueprintable)
class EVENTSSYSTEM_API UESEvent : public UObject
{
	GENERATED_BODY()
	
// Public BP API
public:
	// Invoke the event.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
	static void Invoke(const UESEvent* EventToInvoke, const UESPayload* Payload);

	// Invoke the event on a single actor.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
	static void InvokeOnActor(const UESEvent* EventToInvoke, const UESPayload* Payload, const AActor* Actor);

	// Invoke the event on every actor within a range
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
	static void InvokeOnActorsInRadius(const UESEvent* EventToInvoke, const UESPayload* Payload, FVector Origin, float Radius = 100.0f);

    // Invoke the event on a single widget.
    UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
    static void InvokeOnWidget(const UESEvent* EventToInvoke, const UESPayload* Payload, const UUserWidget* Widget);

// Listeners management
public:
	// Removes all the listeners from one event.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem")
	static void UnRegisterAllListeners(UESEvent* EventToClear);

	// Register the listener to the event.
	void RegisterListener(const IESListenerInterface* Listener);

	// Unregister the listener from the event.
	void UnRegisterListener(const IESListenerInterface* Listener);

// Editor & Debugging
public:
	// Allows the event to write logs.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EventsSystem|Debug")
	bool bWriteLogs;

	// Short description so you won't forget.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EventsSystem|Debug")
	FText Description;

#if defined(UE_BUILD_DEBUG) || defined(UE_EDITOR)
public:
	// Invokes the event for debug purposes.
	void DebugInvoke();
#endif

// Internal functionality
private:
	// Delegate the call to the listeners.
	void CallListeners(const UESPayload* Payload) const;

	// Delegate the call to all the components listeners on the target actor
	void CallListenerComponents(const UESPayload* Payload, const AActor* Actor) const;

	// Delegate the call to all the listeners in rage.
	void CallListenersInRange(const UESPayload* Payload, FVector Origin, float Range) const;

    // Delegate the call to all the widget listeners on the target widget
    void CallListenerWidget(const UESPayload* Payload, const UUserWidget* Widget) const;

// Internal state
private:
	// Listeners registered.
	TSet<const IESListenerInterface*> ActiveListeners;
};
