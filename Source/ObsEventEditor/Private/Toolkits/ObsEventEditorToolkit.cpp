// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ObsEventEditorToolkit.h"

#include "Editor.h"
#include "EditorReimportHandler.h"
#include "EditorStyleSet.h"
#include "SObsEventEditor.h"
#include "ObsEvent.h"
#include "UObject/NameTypes.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FObsEventEditorToolkit"

DEFINE_LOG_CATEGORY_STATIC(LogObsEventEditor, Log, All);


/* Local constants
 *****************************************************************************/

namespace ObsEventEditor
{
	static const FName AppIdentifier("ObsEventEditorApp");
	static const FName TabId("TextEditor");
}


/* FObsEventEditorToolkit structors
 *****************************************************************************/

FObsEventEditorToolkit::FObsEventEditorToolkit(const TSharedRef<ISlateStyle>& InStyle)
	: ObsEvent(nullptr)
	, Style(InStyle)
{ }


FObsEventEditorToolkit::~FObsEventEditorToolkit()
{
	FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
	FReimportManager::Instance()->OnPostReimport().RemoveAll(this);

	GEditor->UnregisterForUndo(this);
}


/* FObsEventEditorToolkit interface
 *****************************************************************************/

void FObsEventEditorToolkit::Initialize(UObsEvent* InObsEvent, const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost)
{
	ObsEvent = InObsEvent;

	// Support undo/redo
	ObsEvent->SetFlags(RF_Transactional);
	GEditor->RegisterForUndo(this);

	// create tab layout
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_ObsEventEditor")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewSplitter()
						->SetOrientation(Orient_Vertical)
						->SetSizeCoefficient(0.66f)
						->Split
						(
							FTabManager::NewStack()
								->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
								->SetHideTabWell(true)
								->SetSizeCoefficient(0.1f)
								
						)
						->Split
						(
							FTabManager::NewStack()
								->AddTab(ObsEventEditor::TabId, ETabState::OpenedTab)
								->SetHideTabWell(true)
								->SetSizeCoefficient(0.9f)
						)
				)
		);

	FAssetEditorToolkit::InitAssetEditor(
		InMode,
		InToolkitHost,
		ObsEventEditor::AppIdentifier,
		Layout,
		true /*bCreateDefaultStandaloneMenu*/,
		true /*bCreateDefaultToolbar*/,
		InObsEvent
	);

	RegenerateMenusAndToolbars();
}


/* FAssetEditorToolkit interface
 *****************************************************************************/

FString FObsEventEditorToolkit::GetDocumentationLink() const
{
	return FString(TEXT("https://github.com/ue4plugins/ObsEvent"));
}


void FObsEventEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_ObsEventEditor", "Text Asset Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(ObsEventEditor::TabId, FOnSpawnTab::CreateSP(this, &FObsEventEditorToolkit::HandleTabManagerSpawnTab, ObsEventEditor::TabId))
		.SetDisplayName(LOCTEXT("TextEditorTabName", "Text Editor"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
}


void FObsEventEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(ObsEventEditor::TabId);
}


/* IToolkit interface
 *****************************************************************************/

FText FObsEventEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Text Asset Editor");
}


FName FObsEventEditorToolkit::GetToolkitFName() const
{
	return FName("ObsEventEditor");
}


FLinearColor FObsEventEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}


FString FObsEventEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "ObsEvent ").ToString();
}


/* FGCObject interface
 *****************************************************************************/

void FObsEventEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(ObsEvent);
}


/* FEditorUndoClient interface
*****************************************************************************/

void FObsEventEditorToolkit::PostUndo(bool bSuccess)
{ }


void FObsEventEditorToolkit::PostRedo(bool bSuccess)
{
	PostUndo(bSuccess);
}


/* FObsEventEditorToolkit callbacks
 *****************************************************************************/

TSharedRef<SDockTab> FObsEventEditorToolkit::HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	TSharedPtr<SWidget> TabWidget = SNullWidget::NullWidget;

	if (TabIdentifier == ObsEventEditor::TabId)
	{
		TabWidget = SNew(SObsEventEditor, ObsEvent, Style);
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			TabWidget.ToSharedRef()
		];
}


#undef LOCTEXT_NAMESPACE
