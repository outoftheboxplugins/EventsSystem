// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ESFactoryNew.h"

#include "ESEvent.h"


/* UEventsSystemFactoryNew structors
 *****************************************************************************/

UEventsSystemFactoryNew::UEventsSystemFactoryNew(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UESEvent::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


/* UFactory overrides
 *****************************************************************************/

UObject* UEventsSystemFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UESEvent>(InParent, InClass, InName, Flags);
}


bool UEventsSystemFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}
