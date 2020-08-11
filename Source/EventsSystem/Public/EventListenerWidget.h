// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

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
//TODO: Make this class blueprint spawnable widget
UCLASS(ClassGroup = (Custom), Category = "ObsEvents", Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent), hidecategories = ("Slot (Canvas Panel Slot)", "Appearance", "Input", "Interaction", "Behavior", "RenderTransform", "Performance", "Clipping", "Navigation") )
class OBSEVENT_API UObsWidgetListener : public UUserWidget, public IObsInterfaceListener
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

public:
	// Called at the start of the game.
	virtual void NativeConstruct() override;

	// Called at the end of the game.
	~UObsWidgetListener();

	// Called when the event is invoked.
	virtual void OnEventCalled(UObsPayload* payload) const override;
};
