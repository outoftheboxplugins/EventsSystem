// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ESListenerInterface.h"

void IESListenerInterface::RegisterListener(UESEvent* Event) const
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

void IESListenerInterface::UnregisterListener(UESEvent* Event) const
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

