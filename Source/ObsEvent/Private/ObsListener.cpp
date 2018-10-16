// Copyright Alexandru pasotee Oprea 2018. All Rights Reserved.

#include "ObsListener.h"
#include "ObsEvent.h"
#include "GameFramework/Actor.h"

UObsListener::OnConstruction()
{
	Super::OnConstruction();

	RegisterListener(eventToListen);
}

UObsListener::~UObsListener()
{
	UnregisterListener(eventToListen);
}

void UObsListener::OnEventCalled() const
{
	OnEventInvoked.Broadcast();
}

