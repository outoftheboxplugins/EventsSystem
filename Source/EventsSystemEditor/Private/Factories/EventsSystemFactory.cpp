// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "EventsSystemFactory.h"

#include "Containers/UnrealString.h"
#include "EventsSystem.h"
#include "Misc/FileHelper.h"


/* UEventsSystemFactory constructors
 *****************************************************************************/

UEventsSystemFactory::UEventsSystemFactory( const FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("txt;")) + NSLOCTEXT("UEventsSystemFactory", "FormatTxt", "Text File").ToString());
	SupportedClass = UEventsSystem::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}


/* UFactory overrides
 *****************************************************************************/

UObject* UEventsSystemFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UEventsSystem* EventsSystem = nullptr;
	FString TextString;

	if (FFileHelper::LoadFileToString(TextString, *Filename))
	{
		EventsSystem = NewObject<UEventsSystem>(InParent, InClass, InName, Flags);
		EventsSystem->Description = FText::FromString(TextString);
	}

	bOutOperationCanceled = false;

	return EventsSystem;
}
