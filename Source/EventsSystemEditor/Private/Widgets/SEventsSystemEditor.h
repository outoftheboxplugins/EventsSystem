// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Templates/SharedPointer.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

class FText;
class ISlateStyle;
class UObsEvent;


/**
 * Implements the UObsEvent asset editor widget.
 */
class SObsEventEditor
	: public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SObsEventEditor) { }
	SLATE_END_ARGS()

public:

	/** Virtual destructor. */
	virtual ~SObsEventEditor();

	/**
	 * Construct this widget
	 *
	 * @param InArgs The declaration data for this widget.
	 * @param InObsEvent The UObsEvent asset to edit.
	 * @param InStyleSet The style set to use.
	 */
	void Construct(const FArguments& InArgs, UObsEvent* InObsEvent, const TSharedRef<ISlateStyle>& InStyle);

private:

	/** Callback for text changes in the editable text box. */
	void HandleEditableTextBoxTextChanged(const FText& NewText);

	/** Callback for committed text in the editable text box. */
	void HandleEditableTextBoxTextCommitted(const FText& Comment, ETextCommit::Type CommitType);

	/** Callback for property changes in the text asset. */
	void HandleObsEventPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);

private:

	/** Holds the editable text box widget. */
	TSharedPtr<SMultiLineEditableTextBox> EditableTextBox;

	/** Pointer to the text asset that is being edited. */
	UObsEvent* ObsEvent;
};
