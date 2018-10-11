// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#include "ObsInterfaceListener.h"

void IObsInterfaceListener::RegisterListener(UObsEvent* ObsEvent) const
{
	UE_LOG(LogTemp, Warning, TEXT("works"))
	if (ObsEvent != nullptr)
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
	if (ObsEvent != nullptr)
	{
		ObsEvent->UnRegisterListener(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing event on listener while unregistering."))
	}
}

