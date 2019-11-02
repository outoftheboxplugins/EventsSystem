// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "EventsSystem.generated.h"

class IObsInterfaceListener;
class AActor;
class UUserWidget;
class UObsPayload;

/**
 * Event holding all the listeners and delegating the call to them.
 */

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "EventsSystems", Blueprintable)
class EVENTSSYSTEM_API UEventsSystem : public UObject
{
	GENERATED_BODY()
	
public:
	// Invoke the event.
	UFUNCTION(BlueprintCallable, Category = "EventsSystems", meta = (AdvancedDisplay = "payload"))
	static void Invoke(UEventsSystem* eventToInvoke, UObsPayload* payload);

	//TODO: Add optional pin to invoke pin for actor only
	// Invoke the event on a single actor.
	UFUNCTION(BlueprintCallable, Category = "EventsSystems", meta = (AdvancedDisplay = "payload"))
	static void InvokeOnActor(AActor* actor, UEventsSystem* eventToInvoke, UObsPayload* payload);

    //TODO: Add optional pin to invoke pin for widget only
    // Invoke the event on a single widget.
    UFUNCTION(BlueprintCallable, Category = "EventsSystems", meta = (AdvancedDisplay = "payload"))
    static void InvokeOnWidget(UUserWidget* widget, UEventsSystem* eventToInvoke, UObsPayload* payload);

	// Removes all the listeners from one event.
	UFUNCTION(BlueprintCallable, Category = "EventsSystems")
	static void UnRegisterAllListeners(UEventsSystem* eventToClear);

	//TODO: Consider putting payload in here as well.
	// Invokes the event for debug purposes.
	void DebugInvoke();

	// Register the listener to the event.
	void RegisterListener(const IObsInterfaceListener* listener);

	// Unregister the listener from the event.
	void UnRegisterListener(const IObsInterfaceListener* listener);
	
	// Short description so you won't forget.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EventsSystems")
	FText Description;

protected:
	// Listeners registered.
	TArray<const IObsInterfaceListener*> listeners;

	// Delegate the call to the listeners.
	void CallListeners(UObsPayload* payload);

	// Delegate the call to all the components listeners on the target actor
	void CallListenerComponents(AActor* actor, UObsPayload* payload);

    // Delegate the call to all the widget listeners on the target widget
    void CallListenerWidgets(UUserWidget* widget, UObsPayload* payload);
};
