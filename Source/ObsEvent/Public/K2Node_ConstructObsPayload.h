#pragma once
#include "K2Node_ConstructObjectFromClass.h"

#include "CoreMinimal.h"
#include "K2Node_ConstructObsPayload.generated.h"

UCLASS()
class UK2Node_ConstructObsPayload : public UK2Node_ConstructObjectFromClass
{
	GENERATED_BODY()
public:
	//~ Begin UEdGraphNode Interface.
	virtual void AllocateDefaultPins() override;
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	//~ End UEdGraphNode Interface.

	//~ Begin UK2Node Interface
	virtual FText GetMenuCategory() const override;
	virtual bool CanUserEditPinAdvancedViewFlag() const override { return true; }
	//~ End UK2Node Interface.

	virtual bool IsSpawnVarPin(UEdGraphPin* Pin) const override;

protected:
	/** Gets the default node title when no class is selected */
	virtual FText GetBaseNodeTitle() const override;
	/** Gets the node title when a class has been selected. */
	virtual FText GetNodeTitleFormat() const override;
	/** Gets base class to use for the 'class' pin.  UObject by default. */
	virtual UClass* GetClassPinBaseClass() const override;

	/** Get the event input pin */
	UEdGraphPin* GetEventPin() const;
};