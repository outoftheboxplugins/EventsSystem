// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ObsInterfaceListener.h"
#include "ObsListener.generated.h"

/**
 * Component listening to event calls.
 */

class UObsEvent;

UCLASS( ClassGroup=(Custom), hidecategories = ("Variable", "Tags", "ComponentReplication", "Activation", "Cooking", "Physics", "LOD", "AssetUserData", "Collision", "Rendering"), meta=(BlueprintSpawnableComponent) )
class OBSEVENT_API UObsListener : public USceneComponent, public IObsInterfaceListener
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

	// Flow if action when the event is called. (Including instigator)
	UPROPERTY(BlueprintAssignable, Category = "ObsEvents")
	FOnEventInstigatorCalled OnEventInstigatorInvoked;
	
	// Flow if action when the event is called. (Including payload)
	UPROPERTY(BlueprintAssignable, Category = "ObsEvents")
	FOnEventPayLoadCalled OnEventPayLoadCalled;

protected:
	// Called at the start of the game.
	virtual void BeginPlay() override;

	// Called at the start of destroying.
	virtual void BeginDestroy() override;

public:
	// Called when the event is invoked.
	virtual void OnEventCalled(AActor* instigator, UObsPayload* payload) const override;
};
