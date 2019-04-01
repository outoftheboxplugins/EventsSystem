// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#include "ObsListener.h"
#include "ObsEvent.h"
#include "GameFramework/Actor.h"

void UObsListener::BeginPlay()
{
	Super::BeginPlay();

	// Register listener if wanted.
	if (bShouldRegisterOnStart)
	{
		RegisterListener(eventToListen);
	}
}

void UObsListener::BeginDestroy()
{
	Super::BeginDestroy();

	UnregisterListener(eventToListen);
}

void UObsListener::OnEventCalled(AActor* instigator, UObsPayload* payload) const
{
	OnEventInvoked.Broadcast();
	OnEventInstigatorInvoked.Broadcast(instigator);
	OnEventPayLoadCalled.Broadcast(payload);
}

