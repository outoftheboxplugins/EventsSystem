// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#include "ObsWidgetListener.h"
#include "ObsEvent.h"
#include "GameFramework/Actor.h"

void UObsWidgetListener::NativeConstruct()
{
	Super::NativeConstruct();

	RegisterListener(eventToListen);
}

UObsWidgetListener::~UObsWidgetListener()
{
	UnregisterListener(eventToListen);
}

void UObsWidgetListener::OnEventCalled() const
{
	OnEventInvoked.Broadcast();
}

