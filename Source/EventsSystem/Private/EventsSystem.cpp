// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "EventsSystem.h"
#include "ObsPayload.h"
#include "ObsInterfaceListener.h"
#include "GameFramework/Actor.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"

void UEventsSystem::Invoke(UEventsSystem* eventToInvoke, UObsPayload* payload)
{
	// Delegate the event to all the listeners.
	if (eventToInvoke)
	{
		eventToInvoke->CallListeners(payload);
	}
}

void UEventsSystem::InvokeOnActor(AActor* actor, UEventsSystem* eventToInvoke, UObsPayload* payload)
{
	if (!actor) return;

	if (eventToInvoke)
	{
		eventToInvoke->CallListenerComponents(actor, payload);
	}
}

void UEventsSystem::InvokeOnWidget(UUserWidget* widget, UEventsSystem* eventToInvoke, UObsPayload* payload)
{
	if (!widget) return;

	if (eventToInvoke)
	{
		eventToInvoke->CallListenerWidgets(widget, payload);
	}
}

void UEventsSystem::UnRegisterAllListeners(UEventsSystem* eventToClear)
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

void UEventsSystem::DebugInvoke()
{
	Invoke(this, nullptr);
}

void UEventsSystem::RegisterListener(const IObsInterfaceListener* newListener)
{
	// If the listener is not already registered, add him.
	if (newListener != nullptr && listeners.Contains(newListener) == false)
	{
		listeners.Add(newListener);
	}
}

void UEventsSystem::UnRegisterListener(const IObsInterfaceListener* oldListener)
{
	// If the listener is now in our list, remove it.
	if (listeners.Contains(oldListener))
	{
		listeners.Remove(oldListener);
	}
}

void UEventsSystem::CallListeners(UObsPayload* payload)
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

void UEventsSystem::CallListenerComponents(AActor* actor, UObsPayload* payload)
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

void UEventsSystem::CallListenerWidgets(UUserWidget* widget, UObsPayload* payload)
{
    if (!widget)
    {
        return;
    }

    TArray<UWidget*> widgets;
    widget->WidgetTree->GetAllWidgets(widgets);

    for (int i = 0; i < widgets.Num(); i++)
    {
        if (widgets[i])
        {
            IObsInterfaceListener* listenerComponent = Cast<IObsInterfaceListener>(widgets[i]);
            if (listenerComponent && listeners.Contains(listenerComponent))
            {
                listenerComponent->OnEventCalled(payload);
            }
        }
    }
}
