// Fill out your copyright notice in the Description page of Project Settings.

#include "ObsEventFactory.h"
#include "ObsEvent.h"

UObsEventFactory::UObsEventFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UObsEvent::StaticClass();
}

UObject* UObsEventFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UObsEvent* NewObjectAsset = NewObject<UObsEvent>(InParent, Class, Name, Flags);
	return NewObjectAsset;
}


