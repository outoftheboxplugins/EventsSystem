// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "Event.h"
#include "EventsSystemPayload.h"
#include "EventListenerInterface.h"
#include "GameFramework/Actor.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"

void UEvent::Invoke(UEvent* eventToInvoke, UEventsSystemPayload* payload)
{
	// Delegate the event to all the listeners.
	if (eventToInvoke)
	{
		eventToInvoke->CallListeners(payload);
	}
}

void UEvent::InvokeOnActor(AActor* actor, UEvent* eventToInvoke, UEventsSystemPayload* payload)
{
	if (!actor) return;

	if (eventToInvoke)
	{
		eventToInvoke->CallListenerComponents(actor, payload);
	}
}

void UEvent::InvokeOnWidget(UUserWidget* widget, UEvent* eventToInvoke, UEventsSystemPayload* payload)
{
	if (!widget) return;

	if (eventToInvoke)
	{
		eventToInvoke->CallListenerWidgets(widget, payload);
	}
}

void UEvent::UnRegisterAllListeners(UEvent* eventToClear)
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

void UEvent::DebugInvoke()
{
	Invoke(this, nullptr);
}

void UEvent::RegisterListener(const IEventListenerInterface* newListener)
{
	// If the listener is not already registered, add him.
	if (newListener != nullptr && listeners.Contains(newListener) == false)
	{
		listeners.Add(newListener);
	}
}

void UEvent::UnRegisterListener(const IEventListenerInterface* oldListener)
{
	// If the listener is now in our list, remove it.
	if (listeners.Contains(oldListener))
	{
		listeners.Remove(oldListener);
	}
}

void UEvent::CallListeners(UEventsSystemPayload* payload)
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

void UEvent::CallListenerComponents(AActor* actor, UEventsSystemPayload* payload)
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
			IEventListenerInterface* listenerComponent = Cast<IEventListenerInterface>(components[i]);
			if (listenerComponent && listeners.Contains(listenerComponent))
			{
				listenerComponent->OnEventCalled(payload);
			}
		}
	}
}

void UEvent::CallListenerWidgets(UUserWidget* widget, UEventsSystemPayload* payload)
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
            IEventListenerInterface* listenerComponent = Cast<IEventListenerInterface>(widgets[i]);
            if (listenerComponent && listeners.Contains(listenerComponent))
            {
                listenerComponent->OnEventCalled(payload);
            }
        }
    }
}
