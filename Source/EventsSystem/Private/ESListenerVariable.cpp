// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#include "ESListenerVariable.h"

#include "ESEvent.h" // for UESEvent

UESListenerVariable* UESListenerVariable::CreateVariableListener(UESEvent* Event, const FParamOnEventCalled& OnEventInvoked, const FParamOnEventWithPayloadInvoked& OnEventWithPayloadInvoked, bool bRegisterOnStart /*= true*/, bool bUnregisterOnEnd /*= true*/)
{
	UESListenerVariable* VariableListener = NewObject<UESListenerVariable>();

	VariableListener->InDelegateCopy = OnEventInvoked;
	VariableListener->InDelegateWithPayloadCopy = OnEventWithPayloadInvoked;

	VariableListener->EventToListen = Event;
	VariableListener->OnEventInvoked.AddUnique(OnEventInvoked);
	VariableListener->OnEventWithPayloadInvoked.AddUnique(OnEventWithPayloadInvoked);
	VariableListener->bShouldRegisterOnStart = bRegisterOnStart;
	VariableListener->bShouldUnRegisterOnEnd = bUnregisterOnEnd;

	VariableListener->StartListener();

	return VariableListener;
}

bool UESListenerVariable::DestroyVariableListener(UESListenerVariable* VariableListener)
{
	if (VariableListener)
	{
		VariableListener->StopListener();

		VariableListener->OnEventInvoked.Remove(VariableListener->InDelegateCopy);
		VariableListener->OnEventWithPayloadInvoked.Remove(VariableListener->InDelegateWithPayloadCopy);

		VariableListener->EventToListen = nullptr;

		return true;
	}

	return false;
}

void UESListenerVariable::OnEventCalled(const UESPayload* Payload) const
{
	OnEventInvoked.Broadcast();
	OnEventWithPayloadInvoked.Broadcast(Payload);
}

FString UESListenerVariable::GetListenerName() const
{
	return GetName();
}

void UESListenerVariable::StartListener()
{
	if (bShouldRegisterOnStart)
	{
		RegisterListener(EventToListen);
	}
}

void UESListenerVariable::StopListener()
{
	if (bShouldUnRegisterOnEnd)
	{
		UnregisterListener(EventToListen);
	}
}