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

UCLASS( ClassGroup=(Custom), hidecategories = (Object, Variable, Transform, Socket), meta=(BlueprintSpawnableComponent) )
class OBSEVENT_API UObsListener : public USceneComponent, public IObsInterfaceListener
{
	GENERATED_BODY()

public:
	// Event to listen to.
	UPROPERTY(EditAnywhere, Category = "ObsEvents", BlueprintReadWrite)
	UObsEvent* eventToListen;

	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "ObsEvents")
	FOnEventCalled OnEventInvoked;

protected:
	//TODO: Find a way to move this to the constructor without loosing event reference.
	// Called at the start of the game.
	virtual void BeginPlay() override;

public:
	// Called at the end of the game.
	~UObsListener();

	// Called when the event is invoked.
	void OnEventCalled() const;
};
