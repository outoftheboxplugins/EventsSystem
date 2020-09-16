// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ESFactory.h"

#include "Containers/UnrealString.h"
#include "ESEvent.h"
#include "Misc/FileHelper.h"


/* UEventsSystemFactory constructors
 *****************************************************************************/

UEventsSystemFactory::UEventsSystemFactory( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("txt;")) + NSLOCTEXT("UEventsSystemFactory", "FormatTxt", "Text File").ToString());
	SupportedClass = UESEvent::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}


/* UFactory overrides
 *****************************************************************************/

UObject* UEventsSystemFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UESEvent* Event = nullptr;
	FString TextString;

	if (FFileHelper::LoadFileToString(TextString, *Filename))
	{
		Event = NewObject<UESEvent>(InParent, InClass, InName, Flags);
		Event->Description = FText::FromString(TextString);
	}

	bOutOperationCanceled = false;

	return Event;
}
