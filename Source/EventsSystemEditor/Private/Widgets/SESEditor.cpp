// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SESEditor.h"

#include "Fonts/SlateFontInfo.h"
#include "Internationalization/Text.h"
#include "ESEvent.h"
#include "UObject/Class.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

#include "ESEditorSettings.h"


#define LOCTEXT_NAMESPACE "SEventsSystemEditor"


/* SEventsSystemEditor interface
 *****************************************************************************/

SEventsSystemEditor::~SEventsSystemEditor()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}


void SEventsSystemEditor::Construct(const FArguments& InArgs, UEvent* InEvent, const TSharedRef<ISlateStyle>& InStyle)
{
	Event = InEvent;

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
					.Text(Event->Description)
			]
	];

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &SEventsSystemEditor::HandleEventPropertyChanged);
}


/* SEventsSystemEditor callbacks
 *****************************************************************************/

void SEventsSystemEditor::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	Event->MarkPackageDirty();
}


void SEventsSystemEditor::HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType)
{
	Event->Description = EditableTextBox->GetText();
}


void SEventsSystemEditor::HandleEventPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object == Event)
	{
		EditableTextBox->SetText(Event->Description);
	}
}


#undef LOCTEXT_NAMESPACE
