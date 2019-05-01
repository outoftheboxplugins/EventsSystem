// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ObsComponentListener.h"
#include "ObsEvent.h"
#include "GameFramework/Actor.h"

void UObsComponentListener::BeginPlay()
{
	Super::BeginPlay();

	// Register listener if wanted.
	if (bShouldRegisterOnStart)
	{
		RegisterListener(eventToListen);
	}
}

void UObsComponentListener::BeginDestroy()
{
	Super::BeginDestroy();

	UnregisterListener(eventToListen);
}

void UObsComponentListener::OnEventCalled(UObsPayload* payload) const
{
	OnEventInvoked.Broadcast();
	OnEventPayloadInvoked.Broadcast(payload);
}

