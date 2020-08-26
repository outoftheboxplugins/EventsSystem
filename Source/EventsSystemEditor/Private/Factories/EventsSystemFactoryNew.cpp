// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EventsSystemFactoryNew.h"

#include "Event.h"


/* UEventsSystemFactoryNew structors
 *****************************************************************************/

UEventsSystemFactoryNew::UEventsSystemFactoryNew(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UEvent::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


/* UFactory overrides
 *****************************************************************************/

UObject* UEventsSystemFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UEvent>(InParent, InClass, InName, Flags);
}


bool UEventsSystemFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}
