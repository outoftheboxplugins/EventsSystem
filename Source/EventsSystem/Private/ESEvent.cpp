// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ESEvent.h"

#include "EventsSystemModule.h"		// for Debugging Logs

#include "ESPayload.h"				// for UESPayload
#include "ESListenerInterface.h"	// for IESListenerInterface

#include "GameFramework/Actor.h"	// for AActor
#include "Blueprint/WidgetTree.h"	// for WidgetTree
#include "Blueprint/UserWidget.h"	// for UUserWidget

//////////////////////////////////////////////////////////////////////////
// Public BP API
/* STATIC */ void UESEvent::Invoke(const UESEvent* EventToInvoke, const UESPayload* Payload)
{
	if (EventToInvoke)
	{
		EventToInvoke->CallListeners(Payload);
	}
}

/* STATIC */ void UESEvent::InvokeOnActor(const UESEvent* EventToInvoke, const UESPayload* Payload, const AActor* Actor)
{
	if (EventToInvoke)
	{
		EventToInvoke->CallListenerComponents(Payload, Actor);
	}
}

/* STATIC */ void UESEvent::InvokeOnActorsInRadius(const UESEvent* EventToInvoke, const UESPayload* Payload, FVector Origin, float Radius /*= 100.0f*/)
{
	if (EventToInvoke)
	{
		EventToInvoke->CallListenersInRange(Payload, Origin, Radius);
	}
}

/* STATIC */ void UESEvent::InvokeOnWidget(const UESEvent* EventToInvoke, const UESPayload* Payload, const UUserWidget* Widget)
{
	if (EventToInvoke)
	{
		EventToInvoke->CallListenerWidget(Payload, Widget);
	}
}

//////////////////////////////////////////////////////////////////////////
// Listeners management
/* STATIC */ void UESEvent::UnRegisterAllListeners(UESEvent* EventToClear)
{
	if (EventToClear)
	{
		EventToClear->ActiveListeners.Empty();
	}
}

void UESEvent::RegisterListener(const IESListenerInterface* NewListener)
{
	if (NewListener)
	{
		bool bAlreadyInSet = false;
		ActiveListeners.Add(NewListener, &bAlreadyInSet);

		if (bAlreadyInSet)
		{
			UE_LOG(LogEventsSystem, Warning, TEXT("Listener already registered. Skipping double registration."));
		}
	}
	else
	{
		UE_LOG(LogEventsSystem, Warning, TEXT("Listener is nullptr."));
	}
}

void UESEvent::UnRegisterListener(const IESListenerInterface* OldListener)
{
	auto OldListenerIt = ActiveListeners.FindId(OldListener);
	if (OldListenerIt.IsValidId())
	{
		ActiveListeners.Remove(OldListenerIt);
	}
	else
	{
		UE_LOG(LogEventsSystem, Warning, TEXT("Listener is not registered to this event."));
	}
}

void UESEvent::DebugInvoke()
{
	Invoke(this, nullptr);
}

void UESEvent::CallListeners(const UESPayload* Payload) const
{
	for (const IESListenerInterface* Listener : ActiveListeners)
	{
		if (Listener)
		{
			Listener->OnEventCalled(Payload);
		}
	}
}

void UESEvent::CallListenersInRange(const UESPayload* payload, FVector origin, float range) const
{

}

void UESEvent::CallListenerComponents(const UESPayload* payload, const AActor* actor) const
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
			IESListenerInterface* listenerComponent = Cast<IESListenerInterface>(components[i]);
			if (listenerComponent && ActiveListeners.Contains(listenerComponent))
			{
				listenerComponent->OnEventCalled(payload);
			}
		}
	}
}

void UESEvent::CallListenerWidget(const UESPayload* payload, const UUserWidget* widget) const
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
            IESListenerInterface* listenerComponent = Cast<IESListenerInterface>(widgets[i]);
            if (listenerComponent && ActiveListeners.Contains(listenerComponent))
            {
                listenerComponent->OnEventCalled(payload);
            }
        }
    }
}
