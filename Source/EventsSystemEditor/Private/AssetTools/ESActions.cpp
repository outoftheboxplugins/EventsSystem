// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "ESActions.h"

#include "ESEvent.h"

#define LOCTEXT_NAMESPACE "EventsSystemEditor"

FEventsSystemActions::FEventsSystemActions()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("OutOfTheBox")), LOCTEXT("OutOfTheBoxCategory", "OutOfTheBox"));
}

bool FEventsSystemActions::CanFilter()
{
	return true;
}

FText FEventsSystemActions::GetName() const
{
	return LOCTEXT("AssetName", "ESEvent");
}

FColor FEventsSystemActions::GetTypeColor() const
{
	return FColor(1, 83, 183);
}

uint32 FEventsSystemActions::GetCategories()
{
	return AssetCategoryBit;
}

UClass* FEventsSystemActions::GetSupportedClass() const
{
	return UESEvent::StaticClass();
}

#undef LOCTEXT_NAMESPACE
