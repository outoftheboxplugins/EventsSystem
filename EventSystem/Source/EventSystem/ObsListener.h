// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ObsListener.generated.h"

class UObsEvent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVENTSYSTEM_API UObsListener : public USceneComponent
{
	GENERATED_BODY()

public:
	// Event to listen to.
	UPROPERTY(EditInstanceOnly, Category = "Observer Events")
	UObsEvent* eventToListen;

	UObsListener();

	// Called when the event is called.
	void OnEventCalled();

	
	
};
