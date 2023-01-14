// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
#include "ESListenerInterface.h"

#include "ESListenerComponent.generated.h"

// Forward declaration EventsSystem Types
class UESEvent;

/**
 * ActorComponent implementation of the IESListenerInteface
 */

UCLASS(ClassGroup = EventsSystem, Category = "EventsSystem", NotBlueprintable, hidecategories = (Object, Sockets, Tags, Component, Activation, Cooking, AssetUserData, Collision), meta=(BlueprintSpawnableComponent))
class EVENTSSYSTEM_API UESListenerComponent : public UActorComponent, public IESListenerInterface
{
	GENERATED_BODY()

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

	// Called at the end of the game.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
// BP Delegates
protected:
	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventCalled OnEventInvoked;
	
	// Flow if action when the event is called. (Including payload)
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventWithPayloadInvoked OnEventWithPayloadInvoked;

// Event Registration
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	UESEvent* EventToListen;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldRegisterOnStart = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldUnRegisterOnEnd = true;
};
