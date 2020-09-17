// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "ESListenerComponent.h"

#include "ESEvent.h" // for UESEvent

void UEventListenerComponent::OnEventCalled(const UESPayload* Payload) const
{
	OnEventInvoked.Broadcast();
	OnEventsSystemPayloadInvoked.Broadcast(Payload);
}

FString UEventListenerComponent::GetListenerName() const
{
	return GetReadableName();
}

void UEventListenerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bShouldRegisterOnStart)
	{
		RegisterListener(EventToListen);
	}
}

void UEventListenerComponent::BeginDestroy()
{
	Super::BeginDestroy();

	if (bShouldUnRegisterOnDestroy)
	{
		UnregisterListener(EventToListen);
	}
}