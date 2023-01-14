// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

#include "Blueprint/UserWidget.h"
#include "ESListenerInterface.h"

#include "ESListenerWidget.generated.h"

// Forward declaration EventsSystem Types
class UESEvent;

/**
 * UserWidget implementation of the IESListenerInteface
 */

UCLASS(ClassGroup = EventsSystem, Category = "EventsSystem", NotBlueprintable, hidecategories = (Object, Apperance, Input, Interaction, Behavior, RenderTransform, Performance, Clipping, Navigation, Localization), meta = (BlueprintSpawnableComponent))
class EVENTSSYSTEM_API UESListenerWidget : public UUserWidget, public IESListenerInterface
{
	GENERATED_BODY()

// IESListenerInterface interface
private:
	// Called when the event is invoked.
	virtual void OnEventCalled(const UESPayload* Payload) const override;

	// Used for debugging logs.
	virtual FString GetListenerName() const override;

// UUserWidget interface
private:
	// Called when the widget is constructed.
	virtual void NativeConstruct() override;

	// Called when the widget is destructed.
	virtual void NativeDestruct() override;

// BP Delegates
protected:
	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventCalled OnEventInvoked;
	
	// Flow if action when the event is called. (Including payload)
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventWithPayloadInvoked OnEventWithPayloadInvoked;

// Event Registration
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	UESEvent* EventToListen;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldRegisterOnStart = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldUnRegisterOnDestroy = true;
};
