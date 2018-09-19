// Copyright 2018 pasotee. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ObsListener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FComponentCustomStartSignature);

class UObsEvent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBSEVENT_API UObsListener : public USceneComponent
{
	GENERATED_BODY()

protected:
	// Runs at the start of the game.
	void BeginPlay() override;

public:
	// Event to listen to.
	UPROPERTY(EditAnywhere, Category = "Observer Events", BlueprintReadWrite)
	UObsEvent* eventToListen;

	// Called when the event is called.
	void OnEventCalled();

	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "Observer Events")
	FComponentCustomStartSignature OnEventInvoked;

	// Called at the end of the game.
	~UObsListener();
};
