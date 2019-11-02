// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ObsInterfaceListener.h"

void IObsInterfaceListener::RegisterListener(UEventsSystem* EventsSystem) const
{
	if (IsValid(EventsSystem))
	{
		EventsSystem->RegisterListener(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing event on listener while registering."))
	}
}

void IObsInterfaceListener::UnregisterListener(UEventsSystem* EventsSystem) const
{
	if (IsValid(EventsSystem))
	{
		EventsSystem->UnRegisterListener(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing event on listener while unregistering."))
	}
}

