// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AssetTypeActions_Base.h"
#include "Templates/SharedPointer.h"

#include "CoreMinimal.h"

/**
 * 
 */
class FObsAssetActions : public FAssetTypeActions_Base
{
public:
	FText GetName() const;
	FColor GetTypeColor() const;
	uint32 GetCategories();
	UClass* GetSupportedClass() const;
};
