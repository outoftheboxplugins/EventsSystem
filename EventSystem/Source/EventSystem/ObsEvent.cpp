// Fill out your copyright notice in the Description page of Project Settings.

#include "ObsEvent.h"
#include "ObsListener.h"

void UObsEvent::Invoke(UObsEvent* eventToInvoke)
{
	eventToInvoke->CallListeners();
}

void UObsEvent::RegisterListener(UObsListener* newListener)
{
	if (listeners.Contains(newListener) == false)
	{
		listeners.Add(newListener);
	}
}

void UObsEvent::CallListeners()
{
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
