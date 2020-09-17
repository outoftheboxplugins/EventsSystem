// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"



















#include "Containers/Array.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "Modules/ModuleManager.h"
#include "Templates/SharedPointer.h"
#include "Toolkits/AssetEditorToolkit.h"

#include "AssetTools/ESActions.h"
#include "Styles/ESEditorStyle.h"

/**
 * Implements the EventsSystemEditor module.
 */
class FEventsSystemEditorModule : public IModuleInterface
{

//IModuleInterface interface
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool SupportsDynamicReloading() override { return true; }




protected:

	/** Registers asset tool actions. */
	void RegisterAssetTools();

	/** Registers a single asset type action. */
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

	/** Unregisters asset tool actions. */
	void UnregisterAssetTools();

private:
	/** The collection of registered asset type actions. */
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;

	/** Holds the plug-ins style set. */
	TSharedPtr<ISlateStyle> Style;
};