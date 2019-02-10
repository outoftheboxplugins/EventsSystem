// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#include "ObsEvent.h"
#include "ObsInterfaceListener.h"
#include "GameFramework/Actor.h"

void UObsEvent::Invoke(UObsEvent* eventToInvoke, AActor* instigator)
{
	// Delegate the event to all the listeners.
	if (eventToInvoke)
	{
		eventToInvoke->CallListeners(instigator);
	}
}

void UObsEvent::InvokeOnActor(AActor* actor, UObsEvent* eventToInvoke, AActor* instigator)
{
	if (!actor) return;

	if (eventToInvoke)
	{
		eventToInvoke->CallListenerComponents(actor, instigator);
	}
}

void UObsEvent::UnRegisterAllListeners(UObsEvent* eventToClear)
{
	// Remove each one of the listeners.
	for (int i = eventToClear->listeners.Num() - 1; i >= 0; i--)
	{
		eventToClear->listeners.RemoveAt(i);
	}
}

void UObsEvent::RegisterListener(const IObsInterfaceListener* newListener)
{
	// If the listener is not already registered, add him.
	if (newListener != nullptr && listeners.Contains(newListener) == false)
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

void UObsEvent::CallListeners(AActor* instigator)
{
	// Call each one of the listeners & remove deleted ones.
	for (int i = listeners.Num() - 1; i >= 0; i--)
	{
		if (listeners[i] == nullptr)
		{
			listeners.RemoveAt(i);
		}
		else
		{
			listeners[i]->OnEventCalled(instigator);
		}
	}
}

void UObsEvent::CallListenerComponents(AActor* actor, AActor* instigator)
{
	TArray<UActorComponent*> components;
	actor->GetComponents(components);

	for (int i = 0; i < components.Num(); i++)
	{
		if (components[i])
		{
			//TODO: Allow for both calling only registered listeners or all of them.
			IObsInterfaceListener* listenerComponent = Cast<IObsInterfaceListener>(components[i]);
			if (listenerComponent && listeners.Contains(listenerComponent))
			{
				listenerComponent->OnEventCalled(instigator);
			}
		}
	}
}
