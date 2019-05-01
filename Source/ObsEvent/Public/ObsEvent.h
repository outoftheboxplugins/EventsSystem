// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "ObsEvent.generated.h"

class IObsInterfaceListener;
class AActor;
class UObsPayload;

/**
 * Event holding all the listeners and delegating the call to them.
 */

UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "ObsEvents", Blueprintable)
class OBSEVENT_API UObsEvent : public UObject
{
	GENERATED_BODY()
	
public:
	// Invoke the event.
	UFUNCTION(BlueprintCallable, Category = "ObsEvents", meta = (AdvancedDisplay = "payload"))
	static void Invoke(UObsEvent* eventToInvoke, UObsPayload* payload);

	//TODO: Add optional pin to invoke pin for actor only
	// Invoke the event on a single actor.
	UFUNCTION(BlueprintCallable, Category = "ObsEvents", meta = (AdvancedDisplay = "payload"))
	static void InvokeOnActor(AActor* actor, UObsEvent* eventToInvoke, UObsPayload* payload);

	// Removes all the listeners from one event.
	UFUNCTION(BlueprintCallable, Category = "ObsEvents")
	static void UnRegisterAllListeners(UObsEvent* eventToClear);

	//TODO: Consider putting payload in here as well.
	// Invokes the event for debug purposes.
	void DebugInvoke();

	// Register the listener to the event.
	void RegisterListener(const IObsInterfaceListener* listener);

	// Unregister the listener from the event.
	void UnRegisterListener(const IObsInterfaceListener* listener);
	
	// Short description so you won't forget.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ObsEvents")
	FText Description;

protected:
	// Listeners registered.
	TArray<const IObsInterfaceListener*> listeners;

	// Delegate the call to the listeners.
	void CallListeners(UObsPayload* payload);

	// Delegate the call to all the components listeners on the target actor
	void CallListenerComponents(AActor* actor, UObsPayload* payload);
};
