// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#include "ESFactory.h"

#include "ESEvent.h" // for UESEvent

UESFactory::UESFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UESEvent::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

bool UESFactory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UESFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UESEvent>(InParent, InClass, InName, Flags);
}