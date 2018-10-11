// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ObsInterfaceListener.h"
#include "ObsListener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FComponentCustomStartSignature);

class UObsEvent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBSEVENT_API UObsListener : public USceneComponent, public IObsInterfaceListener
{
	GENERATED_BODY()

public:
	// Event to listen to.
	UPROPERTY(EditAnywhere, Category = "ObsEvents", BlueprintReadWrite)
	UObsEvent* eventToListen;

	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "ObsEvents")
	FComponentCustomStartSignature OnEventInvoked;

	// Called at the end of the game.
	~UObsListener();

	void OnEventCalled() const;

	//virtual void RegisterListener(UObsEvent* ObsEvent) const override

	//void UnregisterListener(UObsEvent* ObsEvent) const {}

protected:
	// Runs at the start of the game.
	void BeginPlay() override;

};
