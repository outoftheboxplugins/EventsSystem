// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
#pragma once

#include "AssetTypeActions_Base.h"

/**
 * Asset actions for UESEvents.
 */

class FESActions : public FAssetTypeActions_Base
{
public:
	FESActions();

// FAssetTypeActions_Base interface
private:	
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual UClass* GetSupportedClass() const override;

private:
	EAssetTypeCategories::Type AssetCategoryBit;
};
