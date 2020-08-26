// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "EventsSystemFactory.h"

#include "Containers/UnrealString.h"
#include "Event.h"
#include "Misc/FileHelper.h"


/* UEventsSystemFactory constructors
 *****************************************************************************/

UEventsSystemFactory::UEventsSystemFactory( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("txt;")) + NSLOCTEXT("UEventsSystemFactory", "FormatTxt", "Text File").ToString());
	SupportedClass = UEvent::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}


/* UFactory overrides
 *****************************************************************************/

UObject* UEventsSystemFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UEvent* ObsEvent = nullptr;
	FString TextString;

	if (FFileHelper::LoadFileToString(TextString, *Filename))
	{
		ObsEvent = NewObject<UEvent>(InParent, InClass, InName, Flags);
		ObsEvent->Description = FText::FromString(TextString);
	}

	bOutOperationCanceled = false;

	return ObsEvent;
}
