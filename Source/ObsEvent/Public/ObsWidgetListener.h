// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "ObsInterfaceListener.h"
#include "ObsWidgetListener.generated.h"

/**
 * User Widget listening to event calls.
 */

class UObsEvent;

UCLASS(Blueprintable, BlueprintType, Category = "Custom UI Components")
class OBSEVENT_API UObsWidgetListener : public UUserWidget, public IObsInterfaceListener
{
	GENERATED_BODY()

public:
	// Event to listen to.
	UPROPERTY(EditAnywhere, Category = "ObsEvents", BlueprintReadWrite)
	UObsEvent* eventToListen;

	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "ObsEvents")
	FOnEventCalled OnEventInvoked;

public:
	// Called at the start of the game.
	virtual void NativeConstruct() override;

	// Called at the end of the game.
	~UObsWidgetListener();

	// Called when the event is invoked.
	void OnEventCalled() const;
};
