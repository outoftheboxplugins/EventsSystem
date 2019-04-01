// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#include "ObsWidgetListener.h"
#include "ObsEvent.h"
#include "GameFramework/Actor.h"

void UObsWidgetListener::NativeConstruct()
{
	Super::NativeConstruct();

	// Register listener if wanted.
	if (bShouldRegisterOnStart)
	{
		RegisterListener(eventToListen);
	}
}

UObsWidgetListener::~UObsWidgetListener()
{
	UnregisterListener(eventToListen);
}

void UObsWidgetListener::OnEventCalled(AActor* instigator, UObsPayload* payload) const
{
	OnEventInvoked.Broadcast();
	OnEventInstigatorInvoked.Broadcast(instigator);
	OnEventPayLoadCalled.Broadcast(payload);
}

