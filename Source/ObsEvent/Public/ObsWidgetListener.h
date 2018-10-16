// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "ObsInterfaceListener.h"
#include "ObsWidgetListener.generated.h"

class UObsEvent;

UCLASS( )
class OBSEVENT_API UObsWidgetListener : public UWidget, public IObsInterfaceListener
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
	~UObsWidgetListener();

	void OnEventCalled() const;

public:
	// Runs at the start of the game.
	UObsWidgetListener();
	//virtual void NativeConstruct() override;

};
