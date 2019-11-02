// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ObsWidgetListener.h"
#include "EventsSystem.h"
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

void UObsWidgetListener::OnEventCalled(UObsPayload* payload) const
{
	OnEventInvoked.Broadcast();
	OnEventPayloadInvoked.Broadcast(payload);
}

