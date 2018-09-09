// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObsEvent.generated.h"

USTRUCT()
struct FMyItemInfo {

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere)
		FString itemName;

	UPROPERTY(EditAnywhere)
		UTexture2D* itemThumbnail;

	UPROPERTY(EditAnywhere)
		UBlueprint* itemBlueprint;

	UPROPERTY(EditAnywhere)
		FColor itemColor;
};

class UObsListener;

/**
 * Event holding all the listeners and delegating the call to them.
 */
UCLASS(BlueprintType, hidecategories = (Object), ClassGroup = Events, Category = "Eventss", Blueprintable)

class EVENTSYSTEM_API UObsEvent : public UObject
{
	GENERATED_BODY()
	
public:
	// Invoke the event.
	UFUNCTION(BlueprintCallable)
	static void Invoke(UObsEvent* eventToInvoke);

	// Register the listener to the event.
	void RegisterListener(UObsListener* listener);

	// Unregister the listener from the event.
	void UnRegisterListener(UObsListener* listener);
	
	FString Text;
protected:
	// Listeners registered.
	TArray<UObsListener*> listeners;

	// Delegate the call to the listeners.
	void CallListeners();
};
