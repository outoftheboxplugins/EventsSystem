// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "ESListenerInterface.h"
#include "ESListenerWidget.generated.h"

/**
 * User Widget listening to event calls.
 */

class UESEvent;
//TODO: Make this class blueprint spawnable widget
UCLASS(ClassGroup = (Custom), Category = "EventsSystem", Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent), hidecategories = ("Slot (Canvas Panel Slot)", "Appearance", "Input", "Interaction", "Behavior", "RenderTransform", "Performance", "Clipping", "Navigation") )
class EVENTSSYSTEM_API UEventListenerWidget : public UUserWidget, public IESListenerInterface
{
	GENERATED_BODY()

public:
	// Event to listen to.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	UESEvent* eventToListen;

	// Should the listener register on start?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldRegisterOnStart = true;

	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventCalled OnEventInvoked;

	// Flow if action when the event is called. (Including payload)
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventsSystemPayloadCalled OnEventsSystemPayloadInvoked;

public:
	// Called at the start of the game.
	virtual void NativeConstruct() override;

	// Called at the end of the game.
	~UEventListenerWidget();

	// Called when the event is invoked.
	virtual void OnEventCalled(const UESPayload* payload) const override;
};
