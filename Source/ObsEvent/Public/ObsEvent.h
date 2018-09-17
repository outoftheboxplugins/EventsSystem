// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"

#include "ObsEvent.generated.h"


/**
 * Implements an asset that can be used to store arbitrary text, such as notes
 * or documentation.
 */
UCLASS(BlueprintType, hidecategories=(Object))
class UObsEvent
	: public UObject
{
	GENERATED_BODY()

public:

	/** Holds the stored text. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="ObsEvent")
	FText Text;
};
