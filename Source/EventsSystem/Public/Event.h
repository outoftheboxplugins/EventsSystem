// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"

#include "Event.generated.h"

class IEventListenerInterface;
class AActor;
class UUserWidget;
class UEventsSystemPayload;

/**
 * Event holding all the listeners and delegating the call to them.
 */

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "EventsSystem", Blueprintable)
class EVENTSSYSTEM_API UEvent : public UObject
{
	GENERATED_BODY()
	
public:
	// Invoke the event.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "payload"))
	static void Invoke(UEvent* eventToInvoke, UEventsSystemPayload* payload);

	// Invoke the event on a single actor.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "payload"))
	static void InvokeOnActor(AActor* actor, UEvent* eventToInvoke, UEventsSystemPayload* payload);

    // Invoke the event on a single widget.
    UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "payload"))
    static void InvokeOnWidget(UUserWidget* widget, UEvent* eventToInvoke, UEventsSystemPayload* payload);

	// Removes all the listeners from one event.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem")
	static void UnRegisterAllListeners(UEvent* eventToClear);

	//TODO: Consider putting payload in here as well.
	// Invokes the event for debug purposes.
	void DebugInvoke();

	// Register the listener to the event.
	void RegisterListener(const IEventListenerInterface* listener);

	// Unregister the listener from the event.
	void UnRegisterListener(const IEventListenerInterface* listener);
	
	// Short description so you won't forget.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EventsSystem")
	FText Description;

protected:
	// Listeners registered.
	TArray<const IEventListenerInterface*> listeners;

	// Delegate the call to the listeners.
	void CallListeners(UEventsSystemPayload* payload);

	// Delegate the call to all the components listeners on the target actor
	void CallListenerComponents(AActor* actor, UEventsSystemPayload* payload);

    // Delegate the call to all the widget listeners on the target widget
    void CallListenerWidgets(UUserWidget* widget, UEventsSystemPayload* payload);
};
