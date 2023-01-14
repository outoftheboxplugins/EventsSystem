// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#include "ESActions.h"

#include "ESEvent.h" // for UESEvent

#define LOCTEXT_NAMESPACE "EventsSystemEditor"

namespace
{
	FName AssetCategoryRegisterName = FName(TEXT("OutOfTheBox"));
	FText AssetCategoryDisplayName = LOCTEXT("OutOfTheBoxCategory", "OutOfTheBox");
}

FESActions::FESActions()
{
	IAssetTools& AssetTools = FAssetToolsModule::GetModule().Get();
	AssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(AssetCategoryRegisterName, AssetCategoryDisplayName);
}

FText FESActions::GetName() const
{
	return LOCTEXT("AssetName", "Event");
}

FColor FESActions::GetTypeColor() const
{
	return FColor(1, 83, 183);
}

uint32 FESActions::GetCategories()
{
	return AssetCategoryBit;
}

UClass* FESActions::GetSupportedClass() const
{
	return UESEvent::StaticClass();
}

#undef LOCTEXT_NAMESPACE
