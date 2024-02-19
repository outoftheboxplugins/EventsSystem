// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#include "ESEvent.h"

#include "ESLog.h"					// for Debugging Logs
#include "ESPayload.h"				// for UESPayload
#include "ESListenerInterface.h"	// for IESListenerInterface

#include "Blueprint/UserWidget.h" // for UUserWidget
#include "Blueprint/WidgetTree.h" // for WidgetTree
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h" // for AActor

//////////////////////////////////////////////////////////////////////////
// Public BP API
/* STATIC */ void UESEvent::Invoke(const UESEvent* EventToInvoke, const UESPayload* Payload)
{
	if (EventToInvoke)
	{
		if (EventToInvoke->bWriteLogs)
		{
			UE_LOG(LogEventsSystem, Log, TEXT("Event %s invoked."), *EventToInvoke->GetName());
		}

		TSet<const IESListenerInterface*> ActiveListeners = EventToInvoke->ActiveListeners;
		for (const IESListenerInterface* Listener : ActiveListeners)
		{
			if (Listener)
			{
				Listener->OnEventCalled(Payload);
			}
		}
	}
}

/* STATIC */ void UESEvent::InvokeOnActor(const UESEvent* EventToInvoke, const UESPayload* Payload, const AActor* Actor)
{
	if (EventToInvoke && Actor)
	{
		if (EventToInvoke->bWriteLogs)
		{
			UE_LOG(LogEventsSystem, Log, TEXT("Event %s invoked."), *EventToInvoke->GetName());
		}

		TArray<UActorComponent*> ActorComponents;
		Actor->GetComponents(ActorComponents);

		for (UActorComponent* ActorComponent : ActorComponents)
		{
			IESListenerInterface* ListenerComponent = Cast<IESListenerInterface>(ActorComponent);
			if (ListenerComponent && EventToInvoke->ActiveListeners.Contains(ListenerComponent))
			{
				ListenerComponent->OnEventCalled(Payload);
			}
			else if (UWidgetComponent* WidgetComponent = Cast<UWidgetComponent>(ActorComponent))
			{
				InvokeOnWidget(EventToInvoke, Payload, WidgetComponent->GetWidget());
			}
		}
	}
}

/* STATIC */ void UESEvent::InvokeOnActorsInRadius(const UESEvent* EventToInvoke, const UESPayload* Payload, FVector Origin, float Radius /*= 200.0f*/)
{
	if (EventToInvoke)
	{
		if (EventToInvoke->bWriteLogs)
		{
			UE_LOG(LogEventsSystem, Log, TEXT("Event %s invoked."), *EventToInvoke->GetName());
		}
		TSet<const IESListenerInterface*> ActiveListeners = EventToInvoke->ActiveListeners;
		for (const IESListenerInterface* Listener : ActiveListeners)
		{
			if (const UActorComponent* ActorListener = Cast<UActorComponent>(Listener))
			{
				FVector ActorLocation = ActorListener->GetOwner()->GetActorLocation();
				const bool bIsInRange = FVector::Distance(ActorLocation, Origin) <= Radius;
				if (bIsInRange)
				{
					Listener->OnEventCalled(Payload);
				}
			}
		}
	}
}

/* STATIC */ void UESEvent::InvokeOnWidget(const UESEvent* EventToInvoke, const UESPayload* Payload, const UUserWidget* Widget)
{
	if (EventToInvoke && Widget)
	{
		if (EventToInvoke->bWriteLogs)
		{
			UE_LOG(LogEventsSystem, Log, TEXT("Event %s invoked."), *EventToInvoke->GetName());
		}

		TArray<UWidget*> WidgetListeners;
		Widget->WidgetTree->GetAllWidgets(WidgetListeners);

		for (UWidget* WidgetListener : WidgetListeners)
		{
			IESListenerInterface* ListenerComponent = Cast<IESListenerInterface>(WidgetListener);
			if (ListenerComponent && EventToInvoke->ActiveListeners.Contains(ListenerComponent))
			{
				ListenerComponent->OnEventCalled(Payload);
			}
		}
	}
}

/* STATIC */ void UESEvent::UnRegisterAllListeners(UESEvent* EventToClear)
{
	if (EventToClear)
	{
		EventToClear->ActiveListeners.Empty();
		EventToClear->ListenersList.Empty();

		if (EventToClear->bWriteLogs)
		{
			UE_LOG(LogEventsSystem, Log, TEXT("Listeners for event %s cleared."), *EventToClear->GetName());
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Listeners management
void UESEvent::RegisterListener(const IESListenerInterface* NewListener)
{
	if (NewListener)
	{
		bool bAlreadyInSet = false;
		ActiveListeners.Add(NewListener, &bAlreadyInSet);

		if (!bAlreadyInSet)
		{
			ListenersList.Add(NewListener->GetListenerName());
		}
		else if (bWriteLogs)
		{
			UE_LOG(LogEventsSystem, Warning, TEXT("Listener %s already registered to event %s."), *NewListener->GetListenerName(), *GetName());
		}
	}
}

void UESEvent::UnRegisterListener(const IESListenerInterface* OldListener)
{
	auto OldListenerIt = ActiveListeners.FindId(OldListener);
	if (OldListenerIt.IsValidId())
	{
		ActiveListeners.Remove(OldListenerIt);
		ListenersList.RemoveSingle(OldListener->GetListenerName());
	}
	else if (bWriteLogs)
	{
		UE_LOG(LogEventsSystem, Warning, TEXT("Listener %s is not registered to event %s."), *OldListener->GetListenerName(), *GetName());
	}
}
