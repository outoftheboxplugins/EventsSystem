// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ESListenerWidget.h"
#include "ESEvent.h"
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

void UEventListenerWidget::OnEventCalled(const UESPayload* payload) const
{
	OnEventInvoked.Broadcast();
	OnEventsSystemPayloadInvoked.Broadcast(payload);
}

