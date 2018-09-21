// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ObsEventFactoryNew.h"

#include "ObsEvent.h"


/* UObsEventFactoryNew structors
 *****************************************************************************/

UObsEventFactoryNew::UObsEventFactoryNew(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UObsEvent::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}


/* UFactory overrides
 *****************************************************************************/

UObject* UObsEventFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UObsEvent>(InParent, InClass, InName, Flags);
}


bool UObsEventFactoryNew::ShouldShowInNewMenu() const
{
	return true;
}
