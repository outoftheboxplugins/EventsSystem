// Fill out your copyright notice in the Description page of Project Settings.

#include "ObsEventsModule.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"


DEFINE_LOG_CATEGORY(MyGameEditor)

#define LOCTEXT_NAMESPACE "MyGameEditor"

void FObsEventsModule::StartupModule()
{
	
}

void FObsEventsModule::ShutdownModule()
{
	UE_LOG(MyGameEditor, Warning, TEXT("MyGameEditor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE