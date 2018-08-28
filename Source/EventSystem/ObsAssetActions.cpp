// Fill out your copyright notice in the Description page of Project Settings.

#include "ObsAssetActions.h"
#include "ObsEvent.h"

FText FObsAssetActions::GetName() const
{
	return NSLOCTEXT("ObsEvent", "ObsEvent", "ObsEvent");
}

FColor FObsAssetActions::GetTypeColor() const
{
	return FColor::Red;
}

uint32 FObsAssetActions::GetCategories()
{
	return  EAssetTypeCategories::Blueprint | EAssetTypeCategories::Misc;
}

UClass* FObsAssetActions::GetSupportedClass() const
{
	return UObsEvent::StaticClass();
}
