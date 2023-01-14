// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "ESListenerInterface.h"

#include "ESListenerVariable.generated.h"

// Forward declaration EventsSystem Types
class UESEvent;

// Matching delegates with simple dynamic signature to match the Blueprint Assignable ones.
// They allow UFUNCTIONs to be taken by const& as parameters and get binded to listener's delegates.
DECLARE_DYNAMIC_DELEGATE(FParamOnEventCalled);
DECLARE_DYNAMIC_DELEGATE_OneParam(FParamOnEventWithPayloadInvoked, const UESPayload*, Payload);

/**
 * Variable implementation of the IESListenerInteface
 */

UCLASS(ClassGroup = EventsSystem, Category = "EventsSystem", NotBlueprintable, BlueprintType, hidecategories = (Object), meta=(BlueprintSpawnableComponent))
class EVENTSSYSTEM_API UESListenerVariable : public UObject, public IESListenerInterface
{
	GENERATED_BODY()

// Public BP interface
public:
	// Create the listener variable with a set of values.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem", meta = (AutoCreateRefTerm = "OnEventInvoked, OnEventWithPayloadInvoked"))
	static UESListenerVariable* CreateVariableListener(UESEvent* Event, const FParamOnEventCalled& OnEventInvoked, const FParamOnEventWithPayloadInvoked& OnEventWithPayloadInvoked, bool bRegisterOnStart = true, bool bUnregisterOnEnd = true);

	// Create the listener variable with a set of values.
	UFUNCTION(BlueprintCallable, Category = "EventsSystem")
	static bool DestroyVariableListener(UESListenerVariable* VariableListener);

// IESListenerInterface interface
private:
	// Called when the event is invoked.
	virtual void OnEventCalled(const UESPayload* Payload) const override;

	// Used for debugging logs.
	virtual FString GetListenerName() const override;

// Lifetime
private:
	// Call this at the start of the lifetime of the instance
	void StartListener();
	
	// Call this at the end of the lifetime of the instance
	void StopListener();
	
// BP Delegates
protected:
	// Flow of action when the event is called.
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventCalled OnEventInvoked;
	
	// Flow if action when the event is called. (Including payload)
	UPROPERTY(BlueprintAssignable, Category = "EventsSystem")
	FOnEventWithPayloadInvoked OnEventWithPayloadInvoked;

// Event Registration
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	UESEvent* EventToListen;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldRegisterOnStart = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EventsSystem")
	bool bShouldUnRegisterOnEnd = true;

private:
	FParamOnEventCalled InDelegateCopy;

	FParamOnEventWithPayloadInvoked InDelegateWithPayloadCopy;
};
