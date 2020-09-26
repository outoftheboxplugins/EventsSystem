// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "ESListenerComponent.h"

#include "ESEvent.h" // for UESEvent

void UESListenerComponent::OnEventCalled(const UESPayload* Payload) const
{
	OnEventInvoked.Broadcast();
	OnEventsSystemPayloadInvoked.Broadcast(Payload);
}

FString UESListenerComponent::GetListenerName() const
{
	return GetReadableName();
}

void UESListenerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bShouldRegisterOnStart)
	{
		RegisterListener(EventToListen);
	}
}

void UESListenerComponent::BeginDestroy()
{
	Super::BeginDestroy();

	if (bShouldUnRegisterOnDestroy)
	{
		UnregisterListener(EventToListen);
	}
}