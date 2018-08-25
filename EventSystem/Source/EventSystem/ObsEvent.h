// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObsEvent.generated.h"

class UObsListener;

/**
 * Event holding all the listeners and delegating the call to them.
 */
UCLASS()
class EVENTSYSTEM_API UObsEvent : public UObject
{
	GENERATED_BODY()
	
public:
	// Invoke the event.
	UFUNCTION(BlueprintCallable)
	static void Invoke(UObsEvent* eventToInvoke);

	// Register the listener to the event.
	void RegisterListener(UObsListener* listener);
	
protected:
	// Listeners registered.
	TArray<UObsListener*> listeners;

	// Delegate the call to the listeners.
	void CallListeners();
};
