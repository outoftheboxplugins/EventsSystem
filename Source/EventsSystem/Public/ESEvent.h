// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

#include "ESEvent.generated.h"

// Forward declaration UE types
class AActor;
class UUserWidget;

// Forward declaration EventsSystem Types
class IESListenerInterface;
class UESPayload;

/**
 * Event holding all the listeners and delegating the call to them.
 */

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = EventsSystem, Category = "EventsSystem", Blueprintable)
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

	// Invoke the event on every actor within a range.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
	static void InvokeOnActorsInRadius(const UESEvent* EventToInvoke, const UESPayload* Payload, FVector Origin, float Radius = 200.0f);

    // Invoke the event on a single widget.
    UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AdvancedDisplay = "Payload"))
    static void InvokeOnWidget(const UESEvent* EventToInvoke, const UESPayload* Payload, const UUserWidget* Widget);

	// Removes all the listeners from one event.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem")
	static void UnRegisterAllListeners(UESEvent* EventToClear);

// Listeners management
public:	
	// Register the listener to the event.
	void RegisterListener(const IESListenerInterface* Listener);

	// Unregister the listener from the event.
	void UnRegisterListener(const IESListenerInterface* Listener);

// Internal state
private:
	// Listeners registered.
	TSet<const IESListenerInterface*> ActiveListeners;

// Editor & Debugging
public:	
	// Short description so you won't forget.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EventsSystem|Debug", meta = (MultiLine = "true"))
	FText Description;

	// Allows the event to write logs.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EventsSystem|Debug")
	bool bWriteLogs;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "EventsSystem|Debug")
	TArray<FString> ListenersList;
};
