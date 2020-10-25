// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "Factories/Factory.h"
<<<<<<< HEAD:Source/EventsSystemEditor/Private/Factories/EventsSystemFactoryNew.h
#include "UObject/ObjectMacros.h"

#include "EventsSystemFactoryNew.generated.h"
=======
>>>>>>> events-rename:Source/EventsSystemEditor/Private/Factories/ESEventsFactory.h

#include "ESEventsFactory.generated.h"

/**
<<<<<<< HEAD:Source/EventsSystemEditor/Private/Factories/EventsSystemFactoryNew.h
 * Implements a factory for UEventsSystem objects.
 */
UCLASS(hidecategories=Object)
class UEventsSystemFactoryNew
	: public UFactory
=======
 * Factory responsible for creating UESEvents assets.
 */

UCLASS()
class UESEventsFactory : public UFactory
>>>>>>> events-rename:Source/EventsSystemEditor/Private/Factories/ESEventsFactory.h
{
	GENERATED_UCLASS_BODY()

// UFactory interface
public:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
};
