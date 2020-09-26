// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "ESEventsFactory.h"

#include "ESEvent.h"

UESEventsFactory::UESEventsFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UESEvent::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UESEventsFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UESEvent>(InParent, InClass, InName, Flags);
}

bool UESEventsFactory::ShouldShowInNewMenu() const
{
	return true;
}
