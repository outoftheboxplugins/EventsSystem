// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"

#include "CoreMinimal.h"
#include "ObsInterfaceListener.h"
#include "ObsComponentListener.generated.h"

class UEventsSystem;

/**
 * Component listening to event calls.
 */

UCLASS( ClassGroup=(Custom), Category = "EventsSystems", BlueprintType, Blueprintable, hidecategories = ("Variable", "Tags", "ComponentReplication", "Activation", "Cooking", "Physics", "LOD", "AssetUserData", "Collision", "Rendering", "Sockets"), meta=(BlueprintSpawnableComponent) )
class EVENTSSYSTEM_API UObsComponentListener : public UActorComponent, public IObsInterfaceListener
{
	GENERATED_BODY()

public:
	// Event to listen to.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystems")
	UEventsSystem* eventToListen;

	// Should the listener register on start?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystems")
	bool bShouldRegisterOnStart = true;

	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "EventsSystems")
	FOnEventCalled OnEventInvoked;
	
	// Flow if action when the event is called. (Including payload)
	UPROPERTY(BlueprintAssignable, Category = "EventsSystems")
	FOnEventPayLoadCalled OnEventPayloadInvoked;

protected:
	// Called at the start of the game.
	virtual void BeginPlay() override;

	// Called at the start of destroying.
	virtual void BeginDestroy() override;

public:
	// Called when the event is invoked.
	virtual void OnEventCalled(UObsPayload* payload) const override;
};
