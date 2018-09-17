// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ObsEventFactory.h"

#include "Containers/UnrealString.h"
#include "ObsEvent.h"
#include "Misc/FileHelper.h"


/* UObsEventFactory structors
 *****************************************************************************/

UObsEventFactory::UObsEventFactory( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("txt;")) + NSLOCTEXT("UObsEventFactory", "FormatTxt", "Text File").ToString());
	SupportedClass = UObsEvent::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}


/* UFactory overrides
 *****************************************************************************/

/* This is the old API (only for demonstration purposes)
UObject* UObsEventFactory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn)
{
	UObsEvent* ObsEvent = nullptr;
	FString TextString;

	if (FFileHelper::LoadFileToString(TextString, *CurrentFilename))
	{
		ObsEvent = NewObject<UObsEvent>(InParent, Class, Name, Flags);
		ObsEvent->Text = FText::FromString(TextString);
	}

	return ObsEvent;
}*/


UObject* UObsEventFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UObsEvent* ObsEvent = nullptr;
	FString TextString;

	if (FFileHelper::LoadFileToString(TextString, *Filename))
	{
		ObsEvent = NewObject<UObsEvent>(InParent, InClass, InName, Flags);
		ObsEvent->Text = FText::FromString(TextString);
	}

	bOutOperationCanceled = false;

	return ObsEvent;
}
