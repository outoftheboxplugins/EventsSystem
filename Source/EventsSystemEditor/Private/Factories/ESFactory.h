// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

#include "Factories/Factory.h"

#include "ESFactory.generated.h"

/**
 * Factory responsible for creating UESEvents assets.
 */

UCLASS()
class UESFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

// UFactory interface
private:
	virtual bool ShouldShowInNewMenu() const override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
