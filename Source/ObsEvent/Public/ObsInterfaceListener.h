#pragma once

#include "ObsEvent.h"
#include "ObsInterfaceListener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventCalled);

class UObsEvent;

UINTERFACE(Blueprintable)
class UObsInterfaceListener : public UInterface
{
	GENERATED_BODY()
};

class IObsInterfaceListener
{
	GENERATED_BODY()

public:
	virtual void RegisterListener(UObsEvent* ObsEvent) const;

	virtual void UnregisterListener(UObsEvent* ObsEvent) const;

	virtual void OnEventCalled() const {}
};