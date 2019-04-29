// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ObsInterfaceListener.h"
#include "ObsComponentListener.generated.h"

/**
 * Component listening to event calls.
 */

class UObsEvent;

UCLASS( ClassGroup=(Custom), Category = "ObsEvents", BlueprintType, Blueprintable, hidecategories = ("Variable", "Tags", "ComponentReplication", "Activation", "Cooking", "Physics", "LOD", "AssetUserData", "Collision", "Rendering"), meta=(BlueprintSpawnableComponent) )
class OBSEVENT_API UObsComponentListener : public USceneComponent, public IObsInterfaceListener
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
	FOnEventPayLoadCalled OnEventPayLoadCalled;

protected:
	// Called at the start of the game.
	virtual void BeginPlay() override;

	// Called at the start of destroying.
	virtual void BeginDestroy() override;

public:
	// Called when the event is invoked.
	virtual void OnEventCalled(UObsPayload* payload) const override;
};
