// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "ObsEvent.generated.h"

class UObsListener;

/**
 * Event holding all the listeners and delegating the call to them.
 */
UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "Events", Blueprintable)

class OBSEVENT_API UObsEvent : public UObject
{
	GENERATED_BODY()
	
public:
	// Invoke the event.
	UFUNCTION(BlueprintCallable, Category = "ObsEvent")
	static void Invoke(UObsEvent* eventToInvoke);

	// Register the listener to the event.
	void RegisterListener(UObsListener* listener);

	// Unregister the listener from the event.
	void UnRegisterListener(UObsListener* listener);
	
	// Short description so you won't forget.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ObsEvent")
	FText Description;

protected:
	// Listeners registered.
	TArray<UObsListener*> listeners;

	// Delegate the call to the listeners.
	void CallListeners();
};
