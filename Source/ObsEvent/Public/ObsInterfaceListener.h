// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#pragma once

#include "ObsEvent.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "ObsInterfaceListener.generated.h"

/**
 * Interface for creating Event listeners of any type..
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventCalled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventInstigatorCalled, class AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventPayLoadCalled, class UObsPayload*, Payload);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnEventDetailedCalled, class AActor*, Instigator, class UObsPayload*, Payload);

class UObsEvent;

UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class UObsInterfaceListener : public UInterface
{
	GENERATED_BODY()
};

//TODO: Check if we can add and remove them in the interface constructor.

class IObsInterfaceListener
{
	GENERATED_BODY()

public:
	// Adds the current listener to the event's listeners
	UFUNCTION(BlueprintCallable, Category = "ObsEvents")
	virtual void RegisterListener(UObsEvent* ObsEvent) const;

	// Removes the current listener from the event's listeners
	UFUNCTION(BlueprintCallable, Category = "ObsEvents")
	virtual void UnregisterListener(UObsEvent* ObsEvent) const;

	// Sends the invokation to the delegate of the event.
	virtual void OnEventCalled(AActor* instigator, UObsPayload* payload) const {}
};