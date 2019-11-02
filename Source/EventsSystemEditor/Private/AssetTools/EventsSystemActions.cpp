// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

#include "EventsSystemActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EventsSystem.h"
#include "Styling/SlateStyle.h"

#include "EventsSystemEditorToolkit.h"


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

	auto EventsSystems = GetTypedWeakObjectPtrs<UEventsSystem>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("EventsSystem_InvokeEvent", "Debug Invoke Event"),
		LOCTEXT("EventsSystem_InvokeEventToolTip", "Simulate an invoke event for this event."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=] {
		for (auto& Obsevent : EventsSystems)
		{
			if (Obsevent.IsValid())
			{
				Obsevent->DebugInvoke();
			}
		}
	}),
			FCanExecuteAction::CreateLambda([=] {
		for (auto& Obsevent : EventsSystems)
		{
			if (Obsevent.IsValid())
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
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_EventsSystem", "Obs Event");
}

UClass* FEventsSystemActions::GetSupportedClass() const
{
	return UEventsSystem::StaticClass();
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
		auto EventsSystem = Cast<UEventsSystem>(*ObjIt);

		if (EventsSystem != nullptr)
		{
			TSharedRef<FEventsSystemEditorToolkit> EditorToolkit = MakeShareable(new FEventsSystemEditorToolkit(Style));
			EditorToolkit->Initialize(EventsSystem, Mode, EditWithinLevelEditor);
		}
	}
}

#undef LOCTEXT_NAMESPACE
