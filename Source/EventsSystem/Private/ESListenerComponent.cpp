// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#include "ESListenerComponent.h"

#include "ESEvent.h" // for UESEvent

void UESListenerComponent::OnEventCalled(const UESPayload* Payload) const
{
	OnEventInvoked.Broadcast();
	OnEventWithPayloadInvoked.Broadcast(Payload);
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

void UESListenerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (bShouldUnRegisterOnEnd)
	{
		UnregisterListener(EventToListen);
	}
}