// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "ESActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ESEvent.h"
#include "Styling/SlateStyle.h"

#include "ESEditorToolkit.h"


#define LOCTEXT_NAMESPACE "AssetTypeActions"


/* FEventsSystemActions constructors
 *****************************************************************************/

FEventsSystemActions::FEventsSystemActions(const TSharedRef<ISlateStyle>& InStyle)
	: Style(InStyle)
{ }


/* FAssetTypeActions_Base overrides
 *****************************************************************************/

bool FEventsSystemActions::CanFilter()
{
	return true;
}


void FEventsSystemActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);

	auto EventsSystem = GetTypedWeakObjectPtrs<UEvent>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("Event_InvokeEvent", "Debug Invoke Event"),
		LOCTEXT("Event_InvokeEventToolTip", "Simulate an invoke event for this event."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=] {
		for (auto& Event : EventsSystem)
		{
			if (Event.IsValid())
			{
				Event->DebugInvoke();
			}
		}
	}),
			FCanExecuteAction::CreateLambda([=] {
		for (auto& Event : EventsSystem)
		{
			if (Event.IsValid())
			{
				return true;
			}
		}
		return false;
	})
		)
	);
}

uint32 FEventsSystemActions::GetCategories()
{
	return EAssetTypeCategories::Blueprint;
}

FText FEventsSystemActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_EventsSystem", "EventsSystem");
}

UClass* FEventsSystemActions::GetSupportedClass() const
{
	return UEvent::StaticClass();
}

FColor FEventsSystemActions::GetTypeColor() const
{
	return FColor::Blue;
}

bool FEventsSystemActions::HasActions(const TArray<UObject *>& InObjects) const
{
	return true;
}

void FEventsSystemActions::OpenAssetEditor(const TArray<UObject *>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /* = TSharedPtr<IToolkitHost>() */)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
		? EToolkitMode::WorldCentric
		: EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Event = Cast<UEvent>(*ObjIt);

		if (Event != nullptr)
		{
			TSharedRef<FEventsSystemEditorToolkit> EditorToolkit = MakeShareable(new FEventsSystemEditorToolkit(Style));
			EditorToolkit->Initialize(Event, Mode, EditWithinLevelEditor);
		}
	}
}

#undef LOCTEXT_NAMESPACE
