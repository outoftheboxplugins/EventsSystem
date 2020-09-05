// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "Event.h"
#include "EventsSystemPayload.h"
#include "EventListenerInterface.h"
#include "GameFramework/Actor.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "EventsSystemModule.h"

//////////////////////////////////////////////////////////////////////////
// Public BP API
/* STATIC */ void UEvent::Invoke(UEvent* EventToInvoke, UEventsSystemPayload* Payload)
{
	if (EventToInvoke)
	{
		EventToInvoke->CallListeners(Payload);
	}
}

/* STATIC */ void UEvent::InvokeOnActor(UEvent* EventToInvoke, UEventsSystemPayload* Payload, AActor* Actor)
{
	if (EventToInvoke)
	{
		EventToInvoke->CallListenerComponents(Payload, Actor);
	}
}

/* STATIC */ void UEvent::InvokeOnActorsInRadius(UEvent* EventToInvoke, UEventsSystemPayload* Payload, FVector Origin, float Radius /*= 100.0f*/)
{
	if (EventToInvoke)
	{
		EventToInvoke->CallListenersInRange(Payload, Origin, Radius);
	}
}

/* STATIC */ void UEvent::InvokeOnWidget(UUserWidget* Widget, UEvent* EventToInvoke, UEventsSystemPayload* Payload)
{
	if (EventToInvoke)
	{
		EventToInvoke->CallListenerWidget(Widget, Payload);
	}
}

//////////////////////////////////////////////////////////////////////////
// Listeners management
/* STATIC */ void UEvent::UnRegisterAllListeners(UEvent* EventToClear)
{
	if (EventToClear)
	{
		EventToClear->ActiveListeners.Empty();
	}
}

void UEvent::RegisterListener(const IEventListenerInterface* NewListener)
{
	// Try and register the new listener
	if (NewListener)
	{
		bool bAlreadyInSet = false;
		ActiveListeners.Add(NewListener, &bAlreadyInSet);

		if (bAlreadyInSet)
		{
			UE_LOG(LogEventsSystem, Warning, TEXT("Listener already registered. Skipping double registration."));
		}
	}
}

void UEvent::UnRegisterListener(const IEventListenerInterface* OldListener)
{
	// If the listener is now in our list, remove it.
	
	auto OldListenerIt = ActiveListeners.FindId(OldListener);
	if (OldListenerIt.IsValidId())
	{
		ActiveListeners.Remove(OldListenerIt);
	}
	else
	{
		//TODO: Log listener not registered.
	}
}

void UEvent::DebugInvoke()
{
	Invoke(this, nullptr);
}

void UEvent::CallListeners(UEventsSystemPayload* Payload)
{
	for (const IEventListenerInterface*& Listener : ActiveListeners)
	{
		if (Listener)
		{
			Listener->OnEventCalled(Payload);
		}
	}
}

void UEvent::CallListenersInRange(UEventsSystemPayload* payload, FVector origin, float range)
{

}

void UEvent::CallListenerComponents(UEventsSystemPayload* payload, AActor* actor)
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
			if (listenerComponent && ActiveListeners.Contains(listenerComponent))
			{
				listenerComponent->OnEventCalled(payload);
			}
		}
	}
}

void UEvent::CallListenerWidget(UUserWidget* widget, UEventsSystemPayload* payload)
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
            if (listenerComponent && ActiveListeners.Contains(listenerComponent))
            {
                listenerComponent->OnEventCalled(payload);
            }
        }
    }
}
