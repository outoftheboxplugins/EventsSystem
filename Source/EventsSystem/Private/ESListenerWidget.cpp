// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "ESListenerWidget.h"

#include "ESEvent.h"				// for UESEvent
#include "Blueprint/UserWidget.h"	// for UWidgetTree

void UEventListenerWidget::OnEventCalled(const UESPayload* payload) const
{
	OnEventInvoked.Broadcast();
	OnEventsSystemPayloadInvoked.Broadcast(payload);
}

FString UEventListenerWidget::GetListenerName() const
{
	if (WidgetTree)
	{
		return WidgetTree->GetName();
	}

	return FString("InvalidWidgetTree");
}

void UEventListenerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (bShouldRegisterOnStart)
	{
		RegisterListener(EventToListen);
	}
}

void UEventListenerWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	if (bShouldUnRegisterOnDestroy)
	{
		UnregisterListener(EventToListen);
	}
}