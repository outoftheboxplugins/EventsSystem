// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"

#include "CoreMinimal.h"
#include "ObsInterfaceListener.h"
#include "ObsComponentListener.generated.h"

class UObsEvent;

/**
 * Component listening to event calls.
 */

UCLASS( ClassGroup=(Custom), Category = "ObsEvents", BlueprintType, Blueprintable, hidecategories = ("Variable", "Tags", "ComponentReplication", "Activation", "Cooking", "Physics", "LOD", "AssetUserData", "Collision", "Rendering", "Sockets"), meta=(BlueprintSpawnableComponent) )
class OBSEVENT_API UObsComponentListener : public UActorComponent, public IObsInterfaceListener
{
	GENERATED_BODY()

public:
	// Event to listen to.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ObsEvents")
	UObsEvent* eventToListen;

	// Should the listener register on start?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ObsEvents")
	bool bShouldRegisterOnStart = true;

	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "ObsEvents")
	FOnEventCalled OnEventInvoked;
	
	// Flow if action when the event is called. (Including payload)
	UPROPERTY(BlueprintAssignable, Category = "ObsEvents")
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
