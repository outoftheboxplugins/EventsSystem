// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EventsSystemEditorToolkit.h"

#include "Editor.h"
#include "EditorReimportHandler.h"
#include "EditorStyleSet.h"
#include "SEventsSystemEditor.h"
#include "Event.h"
#include "UObject/NameTypes.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FEventsSystemEditorToolkit"

DEFINE_LOG_CATEGORY_STATIC(LogEventsSystemEditor, Log, All);


/* Local constants
 *****************************************************************************/

namespace EventsSystemEditor
{
	static const FName AppIdentifier("EventsSystemEditorApp");
	static const FName TabId("TextEditor");
}


/* FEventsSystemEditorToolkit structors
 *****************************************************************************/

FEventsSystemEditorToolkit::FEventsSystemEditorToolkit(const TSharedRef<ISlateStyle>& InStyle)
	: ObsEvent(nullptr)
	, Style(InStyle)
{ }


FEventsSystemEditorToolkit::~FEventsSystemEditorToolkit()
{
	FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
	FReimportManager::Instance()->OnPostReimport().RemoveAll(this);

	GEditor->UnregisterForUndo(this);
}


/* FEventsSystemEditorToolkit interface
 *****************************************************************************/

void FEventsSystemEditorToolkit::Initialize(UEvent* InObsEvent, const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost)
{
	ObsEvent = InObsEvent;

	// Support undo/redo
	ObsEvent->SetFlags(RF_Transactional);
	GEditor->RegisterForUndo(this);

	// create tab layout
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_EventsSystemEditor")
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
								->AddTab(EventsSystemEditor::TabId, ETabState::OpenedTab)
								->SetHideTabWell(true)
								->SetSizeCoefficient(0.9f)
						)
				)
		);

	FAssetEditorToolkit::InitAssetEditor(
		InMode,
		InToolkitHost,
		EventsSystemEditor::AppIdentifier,
		Layout,
		true /*bCreateDefaultStandaloneMenu*/,
		true /*bCreateDefaultToolbar*/,
		InObsEvent
	);

	RegenerateMenusAndToolbars();
}


/* FAssetEditorToolkit interface
 *****************************************************************************/

FString FEventsSystemEditorToolkit::GetDocumentationLink() const
{
	return FString(TEXT("https://github.com/ue4plugins/ObsEvent"));
}


void FEventsSystemEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_EventsSystemEditor", "Text Asset Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(EventsSystemEditor::TabId, FOnSpawnTab::CreateSP(this, &FEventsSystemEditorToolkit::HandleTabManagerSpawnTab, EventsSystemEditor::TabId))
		.SetDisplayName(LOCTEXT("TextEditorTabName", "Text Editor"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
}


void FEventsSystemEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(EventsSystemEditor::TabId);
}


/* IToolkit interface
 *****************************************************************************/

FText FEventsSystemEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Text Asset Editor");
}


FName FEventsSystemEditorToolkit::GetToolkitFName() const
{
	return FName("EventsSystemEditor");
}


FLinearColor FEventsSystemEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}


FString FEventsSystemEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "ObsEvent ").ToString();
}


/* FGCObject interface
 *****************************************************************************/

void FEventsSystemEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(ObsEvent);
}


/* FEditorUndoClient interface
*****************************************************************************/

void FEventsSystemEditorToolkit::PostUndo(bool bSuccess)
{ }


void FEventsSystemEditorToolkit::PostRedo(bool bSuccess)
{
	PostUndo(bSuccess);
}


/* FEventsSystemEditorToolkit callbacks
 *****************************************************************************/

TSharedRef<SDockTab> FEventsSystemEditorToolkit::HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	TSharedPtr<SWidget> TabWidget = SNullWidget::NullWidget;

	if (TabIdentifier == EventsSystemEditor::TabId)
	{
		TabWidget = SNew(SEventsSystemEditor, ObsEvent, Style);
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			TabWidget.ToSharedRef()
		];
}


#undef LOCTEXT_NAMESPACE
