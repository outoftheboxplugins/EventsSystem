// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "ESListenerInterface.h"

#include "ESListenerComponent.generated.h"

// Forward declaration EventsSystem Types
class UESEvent;

/**
 * ActorComponent implementation of the IESListenerInteface
 */

UCLASS(ClassGroup = EventsSystem, Category = "EventsSystem", NotBlueprintable, hidecategories = (Object, ActorComponent), meta=(BlueprintSpawnableComponent))
class EVENTSSYSTEM_API UEventListenerComponent : public UActorComponent, public IESListenerInterface
{
	GENERATED_BODY()

// Event Registration
public:
	// Event to listen to.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	UESEvent* EventToListen;

	// Should the listener register from the start to the event?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldRegisterOnStart = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldUnRegisterOnDestroy = true;

// BP Delegates
public:
	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventCalled OnEventInvoked;
	
	// Flow if action when the event is called. (Including payload)
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventsSystemPayloadCalled OnEventsSystemPayloadInvoked;

	
// IESListenerInterface interface
private:
	// Called when the event is invoked.
	virtual void OnEventCalled(const UESPayload* Payload) const override;

	// Used for debugging logs.
	virtual FString GetListenerName() const override;

// UActorComponent interface
private:
	// Called at the start of the game.
	virtual void BeginPlay() override;

	// Called at the start of destroying.
	virtual void BeginDestroy() override;
};
