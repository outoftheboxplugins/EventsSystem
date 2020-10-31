// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "Factories/Factory.h"

#include "ESEventsFactory.generated.h"

/**
 * Factory responsible for creating UESEvents assets.
 */

UCLASS()
class UESEventsFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

// UFactory interface
public:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;
};
