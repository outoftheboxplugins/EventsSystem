// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#include "ESListenerInterface.h"

#include "ESLog.h"
#include "ESEvent.h"				// for UESEvent

void IESListenerInterface::OnEventCalled(const UESPayload* Payload) const
{
	UE_LOG(LogEventsSystem, Error, TEXT("Listener %s trying to call IESListenerInterface::OnEventCalled base method."), *GetListenerName());
	checkf(false, TEXT("IESListenerInterface::OnEventCalled base method should never be called. Make sure to override this method in your derived classes."));
}

void IESListenerInterface::RegisterListener(UESEvent* Event) const
{
	if (Event)
	{
		Event->RegisterListener(this);
	}
	else
	{
		FString ListenerName = GetListenerName();
		UE_LOG(LogEventsSystem, Warning, TEXT("Listener %s trying to register to an invalid event."), *ListenerName);
	}
}

void IESListenerInterface::UnregisterListener(UESEvent* Event) const
{
	if (Event)
	{
		Event->UnRegisterListener(this);
	}
	else
	{
		FString ListenerName = GetListenerName();
		UE_LOG(LogEventsSystem, Warning, TEXT("Listener %s trying to unregister from an invalid event."), *ListenerName);
	}
}
