// Copyright Alexandru pasotee Oprea 2018-2019. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "ObsEvent.generated.h"


/**
 * Event holding all the listeners and delegating the call to them.
 */

class IObsInterfaceListener;
class AActor;
class UObsPayload;

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "Events", Blueprintable)
class OBSEVENT_API UObsEvent : public UObject
{
	GENERATED_BODY()
	
public:
	// Invoke the event.
	UFUNCTION(BlueprintCallable, Category = "ObsEvent")
	static void Invoke(UObsEvent* eventToInvoke, AActor* instigator, UObsPayload* payload);

	// Invoke the event on a single actor.
	UFUNCTION(BlueprintCallable, Category = "ObsEvent")
	static void InvokeOnActor(AActor* actor, UObsEvent* eventToInvoke, AActor* instigator, UObsPayload* payload);

	// Removes all the listeners from one event.
	UFUNCTION(BlueprintCallable, Category = "ObsEvent")
	static void UnRegisterAllListeners(UObsEvent* eventToClear);

	// Invokes the event for debug purposes.
	void DebugInvoke();

	// Register the listener to the event.
	void RegisterListener(const IObsInterfaceListener* listener);

	// Unregister the listener from the event.
	void UnRegisterListener(const IObsInterfaceListener* listener);
	
	// Short description so you won't forget.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ObsEvent")
	FText Description;

protected:
	// Listeners registered.
	TArray<const IObsInterfaceListener*> listeners;

	// Delegate the call to the listeners.
	void CallListeners(AActor* instigator, UObsPayload* payload);

	void CallListenerComponents(AActor* actor, AActor* instigator, UObsPayload* payload);
};
