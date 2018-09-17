// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ObsEventActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ObsEvent.h"
#include "Styling/SlateStyle.h"

#include "ObsEventEditorToolkit.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"


/* FObsEventActions constructors
 *****************************************************************************/

FObsEventActions::FObsEventActions(const TSharedRef<ISlateStyle>& InStyle)
	: Style(InStyle)
{ }


/* FAssetTypeActions_Base overrides
 *****************************************************************************/

bool FObsEventActions::CanFilter()
{
	return true;
}


void FObsEventActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);

	auto ObsEvents = GetTypedWeakObjectPtrs<UObsEvent>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("ObsEvent_ReverseText", "Reverse Text"),
		LOCTEXT("ObsEvent_ReverseTextToolTip", "Reverse the text stored in the selected text asset(s)."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=]{
				for (auto& ObsEvent : ObsEvents)
				{
					if (ObsEvent.IsValid() && !ObsEvent->Text.IsEmpty())
					{
						ObsEvent->Text = FText::FromString(ObsEvent->Text.ToString().Reverse());
						ObsEvent->PostEditChange();
						ObsEvent->MarkPackageDirty();
					}
				}
			}),
			FCanExecuteAction::CreateLambda([=] {
				for (auto& ObsEvent : ObsEvents)
				{
					if (ObsEvent.IsValid() && !ObsEvent->Text.IsEmpty())
					{
						return true;
					}
				}
				return false;
			})
		)
	);
}


uint32 FObsEventActions::GetCategories()
{
	return EAssetTypeCategories::Blueprint;
}


FText FObsEventActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ObsEvent", "Text Asset");
}


UClass* FObsEventActions::GetSupportedClass() const
{
	return UObsEvent::StaticClass();
}


FColor FObsEventActions::GetTypeColor() const
{
	return FColor::Red;
}


bool FObsEventActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}


void FObsEventActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
		? EToolkitMode::WorldCentric
		: EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto ObsEvent = Cast<UObsEvent>(*ObjIt);

		if (ObsEvent != nullptr)
		{
			TSharedRef<FObsEventEditorToolkit> EditorToolkit = MakeShareable(new FObsEventEditorToolkit(Style));
			EditorToolkit->Initialize(ObsEvent, Mode, EditWithinLevelEditor);
		}
	}
}


#undef LOCTEXT_NAMESPACE
