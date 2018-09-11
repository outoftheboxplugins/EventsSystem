// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ObsAssetActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ObsEvent.h"
#include "Styling/SlateStyle.h"



#define LOCTEXT_NAMESPACE "AssetTypeActions"


/* FTextAssetActions constructors
 *****************************************************************************/

FObsAssetActions::FObsAssetActions(const TSharedRef<ISlateStyle>& InStyle)
	: Style(InStyle)
{ }


/* FAssetTypeActions_Base overrides
 *****************************************************************************/

bool FObsAssetActions::CanFilter()
{
	return true;
}


void FObsAssetActions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);

	auto TextAssets = GetTypedWeakObjectPtrs<UObsEvent>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("TextAsset_ReverseText", "Reverse Text"),
		LOCTEXT("TextAsset_ReverseTextToolTip", "Reverse the text stored in the selected text asset(s)."),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([=] {
		for (auto& TextAsset : TextAssets)
		{
			if (TextAsset.IsValid() && !TextAsset->Text.IsEmpty())
			{
				TextAsset->Text = TextAsset->Text.Reverse();
				TextAsset->PostEditChange();
				TextAsset->MarkPackageDirty();
			}
		}
	}),
			FCanExecuteAction::CreateLambda([=] {
		for (auto& TextAsset : TextAssets)
		{
			if (TextAsset.IsValid() && !TextAsset->Text.IsEmpty())
			{
				return true;
			}
		}
		return false;
	})
		)
	);
}


uint32 FObsAssetActions::GetCategories()
{
	return EAssetTypeCategories::Blueprint;
}


FText FObsAssetActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ObsEvent", "Obs Event");
}


UClass* FObsAssetActions::GetSupportedClass() const
{
	return UObsEvent::StaticClass();
}


FColor FObsAssetActions::GetTypeColor() const
{
	return FColor::Red;
}


bool FObsAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return true;
}


#undef LOCTEXT_NAMESPACE