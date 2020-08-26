// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "EventListenerComponent.h"
#include "Event.h"
#include "GameFramework/Actor.h"

void UEventListenerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register listener if wanted.
	if (bShouldRegisterOnStart)
	{
		RegisterListener(eventToListen);
	}
}

void UEventListenerComponent::BeginDestroy()
{
	Super::BeginDestroy();

	UnregisterListener(eventToListen);
}

void UEventListenerComponent::OnEventCalled(UEventsSystemPayload* payload) const
{
	OnEventInvoked.Broadcast();
	OnEventsSystemPayloadInvoked.Broadcast(payload);
}

