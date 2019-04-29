// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ObsEvent.h"
#include "ObsPayload.h"
#include "ObsInterfaceListener.h"
#include "GameFramework/Actor.h"

void UObsEvent::Invoke(UObsEvent* eventToInvoke, UObsPayload* payload)
{
	// Delegate the event to all the listeners.
	if (eventToInvoke)
	{
		eventToInvoke->CallListeners(payload);
	}
}

void UObsEvent::InvokeOnActor(AActor* actor, UObsEvent* eventToInvoke, UObsPayload* payload)
{
	if (!actor) return;

	if (eventToInvoke)
	{
		eventToInvoke->CallListenerComponents(actor, payload);
	}
}

void UObsEvent::UnRegisterAllListeners(UObsEvent* eventToClear)
{
	if (!eventToClear)
	{
		return;
	}

	// Remove each one of the listeners.
	for (int i = eventToClear->listeners.Num() - 1; i >= 0; i--)
	{
		eventToClear->listeners.RemoveAt(i);
	}
}

void UObsEvent::DebugInvoke()
{
	Invoke(this, nullptr);
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

void UObsEvent::CallListeners(UObsPayload* payload)
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
			listeners[i]->OnEventCalled(payload);
		}
	}
}

void UObsEvent::CallListenerComponents(AActor* actor, UObsPayload* payload)
{
	if (!actor)
	{
		return;
	}

	TArray<UActorComponent*> components;
	actor->GetComponents(components);

	for (int i = 0; i < components.Num(); i++)
	{
		if (components[i])
		{
			IObsInterfaceListener* listenerComponent = Cast<IObsInterfaceListener>(components[i]);
			if (listenerComponent && listeners.Contains(listenerComponent))
			{
				listenerComponent->OnEventCalled(payload);
			}
		}
	}
}
