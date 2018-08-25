// Fill out your copyright notice in the Description page of Project Settings.

#include "ObsListener.h"
#include "ObsEvent.h"

UObsListener::UObsListener()
{
	if (eventToListen != nullptr)
	{
		eventToListen->RegisterListener(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing event on %s"), *GetOwner()->GetName())
	}
}

void UObsListener::OnEventCalled()
{
	UE_LOG(LogTemp, Warning, TEXT("called."))
}

