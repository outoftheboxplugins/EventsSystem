// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "ObsEvent.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "ObsInterfaceListener.generated.h"

/**
 * Interface for creating Event listeners of any type.
 */
//TODO: Hide more categories on the classes inherited from this.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventCalled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventPayLoadCalled, class UObsPayload*, Payload);

class UObsEvent;

UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class UObsInterfaceListener : public UInterface
{
	GENERATED_BODY()
};

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

	// Sends the invoke to the delegate of the event.
	virtual void OnEventCalled(UObsPayload* payload) const {}
};