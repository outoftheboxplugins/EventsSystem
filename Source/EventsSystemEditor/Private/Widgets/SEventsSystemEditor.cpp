// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SEventsSystemEditor.h"

#include "Fonts/SlateFontInfo.h"
#include "Internationalization/Text.h"
#include "EventsSystem.h"
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


void SEventsSystemEditor::Construct(const FArguments& InArgs, UEventsSystem* InEventsSystem, const TSharedRef<ISlateStyle>& InStyle)
{
	EventsSystem = InEventsSystem;

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
					.Text(EventsSystem->Description)
			]
	];

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &SEventsSystemEditor::HandleEventsSystemPropertyChanged);
}


/* SEventsSystemEditor callbacks
 *****************************************************************************/

void SEventsSystemEditor::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	EventsSystem->MarkPackageDirty();
}


void SEventsSystemEditor::HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType)
{
	EventsSystem->Description = EditableTextBox->GetText();
}


void SEventsSystemEditor::HandleEventsSystemPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object == EventsSystem)
	{
		EditableTextBox->SetText(EventsSystem->Description);
	}
}


#undef LOCTEXT_NAMESPACE
