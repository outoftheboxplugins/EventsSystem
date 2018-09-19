// Copyright 2018 pasotee. All Rights Reserved.

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
	UFUNCTION(BlueprintCallable)
	static void Invoke(UObsEvent* eventToInvoke);

	// Register the listener to the event.
	void RegisterListener(UObsListener* listener);

	// Unregister the listener from the event.
	void UnRegisterListener(UObsListener* listener);
	
	/** Holds the stored text. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ObsEvent")
	FText Text;
protected:
	// Listeners registered.
	TArray<UObsListener*> listeners;

	// Delegate the call to the listeners.
	void CallListeners();
};
