// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ObsEventFactory.h"

#include "Containers/UnrealString.h"
#include "ObsEvent.h"
#include "Misc/FileHelper.h"


/* UObsEventFactory constructors
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

UObject* UObsEventFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UObsEvent* ObsEvent = nullptr;
	FString TextString;

	if (FFileHelper::LoadFileToString(TextString, *Filename))
	{
		ObsEvent = NewObject<UObsEvent>(InParent, InClass, InName, Flags);
		ObsEvent->Description = FText::FromString(TextString);
	}

	bOutOperationCanceled = false;

	return ObsEvent;
}
