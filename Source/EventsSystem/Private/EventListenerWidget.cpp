// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "EventListenerWidget.h"
#include "ObsEvent.h"
#include "GameFramework/Actor.h"

void UEventListenerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Register listener if wanted.
	if (bShouldRegisterOnStart)
	{
		RegisterListener(eventToListen);
	}
}

UEventListenerWidget::~UEventListenerWidget()
{
	UnregisterListener(eventToListen);
}

void UEventListenerWidget::OnEventCalled(UEventsSystemPayload* payload) const
{
	OnEventInvoked.Broadcast();
	OnEventsSystemPayloadInvoked.Broadcast(payload);
}

