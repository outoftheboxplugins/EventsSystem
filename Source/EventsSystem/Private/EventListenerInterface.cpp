// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ObsInterfaceListener.h"

void IObsInterfaceListener::RegisterListener(UObsEvent* ObsEvent) const
{
	if (IsValid(ObsEvent))
	{
		ObsEvent->RegisterListener(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing event on listener while registering."))
	}
}

void IObsInterfaceListener::UnregisterListener(UObsEvent* ObsEvent) const
{
	if (IsValid(ObsEvent))
	{
		ObsEvent->UnRegisterListener(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing event on listener while unregistering."))
	}
}

