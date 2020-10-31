// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#include "ESActions.h"

#include "ESEvent.h"

#define LOCTEXT_NAMESPACE "EventsSystemEditor"

FESActions::FESActions()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("OutOfTheBox")), LOCTEXT("OutOfTheBoxCategory", "OutOfTheBox"));
}

bool FESActions::CanFilter()
{
	return true;
}

FText FESActions::GetName() const
{
	return LOCTEXT("AssetName", "ESEvent");
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
