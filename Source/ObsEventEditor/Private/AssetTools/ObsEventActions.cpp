// Copyright Out-of-the-Box Plugins 2018-2019. All Rights Reserved.

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
		LOCTEXT("ObsEvent_InvokeEvent", "Debug Invoke Event"),
		LOCTEXT("ObsEvent_InvokeEventToolTip", "Simulate an invoke event for this event."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=] {
		for (auto& Obsevent : ObsEvents)
		{
			if (Obsevent.IsValid())
			{
				Obsevent->DebugInvoke();
			}
		}
	}),
			FCanExecuteAction::CreateLambda([=] {
		for (auto& Obsevent : ObsEvents)
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

uint32 FObsEventActions::GetCategories()
{
	return EAssetTypeCategories::Blueprint;
}

FText FObsEventActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ObsEvent", "Obs Event");
}

UClass* FObsEventActions::GetSupportedClass() const
{
	return UObsEvent::StaticClass();
}

FColor FObsEventActions::GetTypeColor() const
{
	return FColor::Blue;
}

bool FObsEventActions::HasActions(const TArray<UObject *>& InObjects) const
{
	return true;
}

void FObsEventActions::OpenAssetEditor(const TArray<UObject *>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /* = TSharedPtr<IToolkitHost>() */)
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
