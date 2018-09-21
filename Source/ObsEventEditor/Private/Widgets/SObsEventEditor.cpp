// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SObsEventEditor.h"

#include "Fonts/SlateFontInfo.h"
#include "Internationalization/Text.h"
#include "ObsEvent.h"
#include "UObject/Class.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

#include "ObsEventEditorSettings.h"


#define LOCTEXT_NAMESPACE "SObsEventEditor"


/* SObsEventEditor interface
 *****************************************************************************/

SObsEventEditor::~SObsEventEditor()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}


void SObsEventEditor::Construct(const FArguments& InArgs, UObsEvent* InObsEvent, const TSharedRef<ISlateStyle>& InStyle)
{
	ObsEvent = InObsEvent;

	auto Settings = GetDefault<UObsEventEditorSettings>();

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
					.OnTextChanged(this, &SObsEventEditor::HandleEditableTextBoxTextChanged)
					.OnTextCommitted(this, &SObsEventEditor::HandleEditableTextBoxTextCommitted)
					.Text(ObsEvent->Description)
			]
	];

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &SObsEventEditor::HandleObsEventPropertyChanged);
}


/* SObsEventEditor callbacks
 *****************************************************************************/

void SObsEventEditor::HandleEditableTextBoxTextChanged(const FText& NewText)
{
	ObsEvent->MarkPackageDirty();
}


void SObsEventEditor::HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType)
{
	ObsEvent->Description = EditableTextBox->GetText();
}


void SObsEventEditor::HandleObsEventPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (Object == ObsEvent)
	{
		EditableTextBox->SetText(ObsEvent->Description);
	}
}


#undef LOCTEXT_NAMESPACE
