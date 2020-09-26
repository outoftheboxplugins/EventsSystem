// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "AssetTypeActions_Base.h"

/**
 * Asset actions for UESEvents.
 */

class FEventsSystemActions : public FAssetTypeActions_Base
{
public:
	FEventsSystemActions();

// FAssetTypeActions_Base interface
public:	
	virtual bool CanFilter() override;
	
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual UClass* GetSupportedClass() const override;

private:
	EAssetTypeCategories::Type AssetCategoryBit;
};
