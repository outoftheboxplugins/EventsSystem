// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#include "ObsEvent.h"
#include "ObsInterfaceListener.h"

void UObsEvent::Invoke(UObsEvent* eventToInvoke)
{
	// Delegate the event to all the listeners.
	eventToInvoke->CallListeners();
}

void UObsEvent::RegisterListener(const IObsInterfaceListener* newListener)
{
	// If the listener is not already registered, add him.
	if (listeners.Contains(newListener) == false)
	{
		listeners.Add(newListener);
	}
}

void UObsEvent::UnRegisterListener(const IObsInterfaceListener* oldListener)
{
	// If the listener is now in our list, remove it.
	if (listeners.Contains(oldListener))
	{
		listeners.Remove(oldListener);
	}
}

void UObsEvent::CallListeners()
{
	// Call each of the listeners & remove deleted ones.
	for (int i = listeners.Num() - 1; i >= 0; i--)
	{
		if (listeners[i] == nullptr)
		{
			listeners.RemoveAt(i);
		}
		else
		{
			listeners[i]->OnEventCalled();
		}
	}
}
