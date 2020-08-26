// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SEventsSystemEditor.h"

#include "Fonts/SlateFontInfo.h"
#include "Internationalization/Text.h"
#include "Event.h"
#include "UObject/Class.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

#include "EventsSystemEditorSettings.h"


#define LOCTEXT_NAMESPACE "SEventsSystemEditor"


/* SEventsSystemEditor interface
 *****************************************************************************/

SEventsSystemEditor::~SEventsSystemEditor()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}


void SEventsSystemEditor::Construct(const FArguments& InArgs, UEvent* InObsEvent, const TSharedRef<ISlateStyle>& InStyle)
{
	ObsEvent = InObsEvent;

	auto Settings = GetDefault<UEventsSystemEditorSettings>();

	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SAssignNew(EditableTextBox, SMultiLineEditableTextBox)
					.BackgroundColor((Settings != nullptr) ? Settings->BackgroundColor : FLinearColor::White)
					.Font((Settings != nullptr) ? Settings->Font : FSlateFontInfo())
					.ForegroundColor((Settings != nullptr) ? Settings->ForegroundColor : FLinearColor::Black)
					.Margin((Settings != nullptr) ? Settings->Margin : 4.0f)
					.OnTextChanged(this, &SEventsSystemEditor::HandleEditableTextBoxTextChanged)
					.OnTextCommitted(this, &SEventsSystemEditor::HandleEditableTextBoxTextCommitted)
					.Text(ObsEvent->Description)
			]
	];

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &SEventsSystemEditor::HandleObsEventPropertyChanged);
}


/* SEventsSystemEditor callbacks
 *****************************************************************************/

void SEventsSystemEditor::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	ObsEvent->MarkPackageDirty();
}


void SEventsSystemEditor::HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType)
{
	ObsEvent->Description = EditableTextBox->GetText();
}


void SEventsSystemEditor::HandleObsEventPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object == ObsEvent)
	{
		EditableTextBox->SetText(ObsEvent->Description);
	}
}


#undef LOCTEXT_NAMESPACE
