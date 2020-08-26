// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "EventListenerInterface.h"

void IEventListenerInterface::RegisterListener(UEvent* Event) const
{
	if (IsValid(Event))
	{
		Event->RegisterListener(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing event on listener while registering."))
	}
}

void IEventListenerInterface::UnregisterListener(UEvent* Event) const
{
	if (IsValid(Event))
	{
		Event->UnRegisterListener(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing event on listener while unregistering."))
	}
}

