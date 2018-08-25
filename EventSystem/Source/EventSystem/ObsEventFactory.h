// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ObsEventFactory.generated.h"

/**
 * Creats events in the Content browser.
 */
UCLASS()
class EVENTSYSTEM_API UObsEventFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	// Constructor to allow creation
	UObsEventFactory(const FObjectInitializer & ObjectInitializer);
	
	// Creating the asset itself.
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
