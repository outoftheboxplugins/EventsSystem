// Copyright 2018 pasotee. All Rights Reserved.

#include "ObsListener.h"
#include "ObsEvent.h"

void UObsListener::BeginPlay()
{
	Super::BeginPlay();

	// Check if we have an event set and register to it.
	if (eventToListen == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing event on %s with name %s"), *GetOwner()->GetName(), *GetName())
	}
	else
	{
		eventToListen->RegisterListener(this);		
	}
}

void UObsListener::OnEventCalled()
{
	// Perform the event specific behavior.
	OnEventInvoked.Broadcast();
}

UObsListener::~UObsListener()
{
	// Remove self form listeners when deleted.
	if (eventToListen != nullptr)
	{
		eventToListen->UnRegisterListener(this);
	}
}

