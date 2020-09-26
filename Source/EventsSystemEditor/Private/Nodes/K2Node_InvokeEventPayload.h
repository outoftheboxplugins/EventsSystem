// Copyright Out-of-the-Box Plugins 2018-2020. All Rights Reserved.

#pragma once

#include "K2Node_ConstructObjectFromClass.h"

#include "CoreMinimal.h"
#include "K2Node_InvokeEventPayload.generated.h"

UCLASS(meta = (Keywords = "events system invoke event"))
class UK2Node_InvokeEventPayload : public UK2Node_ConstructObjectFromClass
{
public:
    GENERATED_UCLASS_BODY()

// UK2Node_ConstructObjectFromClass interface
private:
	virtual bool IsSpawnVarPin(UEdGraphPin* Pin) const override;
	virtual FText GetBaseNodeTitle() const override;
	virtual FText GetNodeTitleFormat() const override;
	virtual UClass* GetClassPinBaseClass() const override;

// UEdGraphNode interface
private:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual bool CanUserEditPinAdvancedViewFlag() const override { return true; }

// UK2Node interface
private:
	virtual FText GetMenuCategory() const override;

// Helpers
private:
	UEdGraphPin* GetEventPin() const;
};