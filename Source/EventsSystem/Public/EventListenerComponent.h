// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"

#include "CoreMinimal.h"
#include "EventListenerInterface.h"
#include "EventListenerComponent.generated.h"

class UEvent;

/**
 * Component listening to event calls.
 */

UCLASS( ClassGroup=(Custom), Category = "EventsSystem", BlueprintType, Blueprintable, hidecategories = ("Variable", "Tags", "ComponentReplication", "Activation", "Cooking", "Physics", "LOD", "AssetUserData", "Collision", "Rendering", "Sockets"), meta=(BlueprintSpawnableComponent) )
class EVENTSSYSTEM_API UEventListenerComponent : public UActorComponent, public IEventListenerInterface
{
	GENERATED_BODY()

public:
	// Event to listen to.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	UEvent* eventToListen;

	// Should the listener register on start?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldRegisterOnStart = true;

	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventCalled OnEventInvoked;
	
	// Flow if action when the event is called. (Including payload)
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventsSystemPayloadCalled OnEventsSystemPayloadInvoked;

protected:
	// Called at the start of the game.
	virtual void BeginPlay() override;

	// Called at the start of destroying.
	virtual void BeginDestroy() override;

public:
	// Called when the event is invoked.
	virtual void OnEventCalled(UEventsSystemPayload* payload) const override;
};
