// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateColor.h"
#include "UObject/ObjectMacros.h"

#include "ESEditorSettings.generated.h"


UCLASS(config=Editor)
class EVENTSSYSTEMEDITOR_API UEventsSystemEditorSettings
	: public UObject
{
	GENERATED_BODY()

public:

	/** Color of the EventsSystem editor's background. */
	UPROPERTY(config, EditAnywhere, Category=Appearance)
	FSlateColor BackgroundColor;

	/** Color of the EventsSystem editor's text. */
	UPROPERTY(config, EditAnywhere, Category=Appearance)
	FSlateColor ForegroundColor;

	/** The font to use in the EventsSystem editor window. */
	UPROPERTY(config, EditAnywhere, Category=Appearance)
	FSlateFontInfo Font;

	/** The margin around the EventsSystem editor window (in pixels). */
	UPROPERTY(config, EditAnywhere, Category=Appearance)
	float Margin;

public:

	/** Default constructor. */
	UEventsSystemEditorSettings();
};
