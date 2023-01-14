// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#include "ESListenerWidget.h"

#include "Blueprint/WidgetTree.h"
#include "ESEvent.h"				// for UESEvent
#include "Blueprint/UserWidget.h"	// for UWidgetTree

void UESListenerWidget::OnEventCalled(const UESPayload* payload) const
{
	OnEventInvoked.Broadcast();
	OnEventWithPayloadInvoked.Broadcast(payload);
}

FString UESListenerWidget::GetListenerName() const
{
	if (WidgetTree)
	{
		return WidgetTree->GetName();
	}

	return FString("InvalidWidgetTree");
}

void UESListenerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (bShouldRegisterOnStart)
	{
		RegisterListener(EventToListen);
	}
}

void UESListenerWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	if (bShouldUnRegisterOnDestroy)
	{
		UnregisterListener(EventToListen);
	}
}
