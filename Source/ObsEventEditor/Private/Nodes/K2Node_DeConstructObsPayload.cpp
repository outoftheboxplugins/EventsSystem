#include "Nodes/K2Node_DeConstructObsPayload.h"

#include "EdGraph/EdGraphNode.h"
#include "EdGraphSchema_K2.h"
#include "ObsPayload.h"
#include "BlueprintEditorUtils.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "KismetCompilerMisc.h"
#include "K2Node_CallFunction.h"
#include "AssertionMacros.h"
#include "Kismet/KismetSystemLibrary.h"
#include "KismetCompiler.h"


#define LOCTEXT_NAMESPACE "K2Node_DeConstructObsPayload"

struct FDeConstGetPinName {

	static const FName& GetPayloadClassTextPin() {
		static const FName PayloadClassTextPin(TEXT("Payload data class"));
		return PayloadClassTextPin;
	}

	static const FName& GetPayloadInstanceTextPin() {
		static const FName PayloadInstanceTextPin(TEXT("Payload Instance"));
		return PayloadInstanceTextPin;
	}

	static const FName& GetWorldContextTextPin() {
		static const FName WorldContextTextPin(TEXT("WorldContextObject"));
		return WorldContextTextPin;
	}
};

void UK2Node_DeConstructObsPayload::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	//Input
	UEdGraphPin* InPayloadClassPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Class, UObsPayload::StaticClass(), FDeConstGetPinName::GetPayloadClassTextPin());
	UEdGraphPin* InPayloadinstancePin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObsPayload::StaticClass(), FDeConstGetPinName::GetPayloadInstanceTextPin());
	UEdGraphPin* InWorldContextPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), FDeConstGetPinName::GetWorldContextTextPin());

	// Result pin
	UEdGraphPin* ResultPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, UObsPayload::StaticClass(), UEdGraphSchema_K2::PN_ReturnValue);
}

FText UK2Node_DeConstructObsPayload::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("ConstructObsPayloadK2Node_Title", "Break Obs Payload");
}

FText UK2Node_DeConstructObsPayload::GetTooltipText() const
{
	return LOCTEXT("ConstructObsPayloadK2Node_Tooltip", "Get all the variables from an obs payload instance.");
}

void UK2Node_DeConstructObsPayload::GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const
{
	//TODO: implement these.
	//if (UEdGraphPin* ClassPin = GetClassPin())
	//{
	//	SetPinToolTip(*ClassPin, LOCTEXT("ClassPinDescription", "The object class you want to construct"));
	//}
	//if (UEdGraphPin* OuterPin = (UseOuter() ? GetOuterPin() : nullptr))
	//{
	//	SetPinToolTip(*OuterPin, LOCTEXT("OuterPinDescription", "Owner of the constructed object"));
	//}
	//
	return Super::GetPinHoverText(Pin, HoverTextOut);
}

void UK2Node_DeConstructObsPayload::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	if (Pin && (Pin->PinName == FDeConstGetPinName::GetPayloadClassTextPin()))
	{
		OnClassPinChanged();
	}
}

void UK2Node_DeConstructObsPayload::PinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::PinConnectionListChanged(Pin);

	if (Pin && (Pin->PinName == FDeConstGetPinName::GetPayloadClassTextPin()))
	{
		OnClassPinChanged();
	}
}

FText UK2Node_DeConstructObsPayload::GetMenuCategory() const
{
	return LOCTEXT("ConstructObsPayloadK2Node_MenuCategory", "ObsEvents");
}

void UK2Node_DeConstructObsPayload::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	AllocateDefaultPins();
	if (UClass* UseSpawnClass = GetClassToSpawn(&OldPins))
	{
		CreatePinsForClass(UseSpawnClass);
	}
	RestoreSplitPins(OldPins);
}

void UK2Node_DeConstructObsPayload::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallCreateNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UKismetSystemLibrary, PrintString), UKismetSystemLibrary::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	UClass* ClassToSpawn = GetClassToSpawn();

	bool bSucceeded = true;

	//connect exe
	{
		UEdGraphPin* SpawnExecPin = GetExecPin();
		UEdGraphPin* CallExecPin = CallCreateNode->GetExecPin();
		bSucceeded &= SpawnExecPin && CallExecPin && CompilerContext.MovePinLinksToIntermediate(*SpawnExecPin, *CallExecPin).CanSafeConnect();
	}

	//connect world context
	{
		UEdGraphPin* SpawnOuterPin = GetWorldContextPin();
		UEdGraphPin* CallOuterPin = CallCreateNode->FindPin(TEXT("WorldContextObject"));
		bSucceeded &= SpawnOuterPin && CallOuterPin && CompilerContext.MovePinLinksToIntermediate(*SpawnOuterPin, *CallOuterPin).CanSafeConnect();
	}

	//assign exposed values and connect then
	{
		UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, this, GetResultPin(), ClassToSpawn);
		UEdGraphPin* SpawnNodeThen = GetThenPin();
		bSucceeded &= SpawnNodeThen && LastThen && CompilerContext.MovePinLinksToIntermediate(*SpawnNodeThen, *LastThen).CanSafeConnect();
	}

	BreakAllNodeLinks();

	if (!bSucceeded)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("GenericCreateObject_Error", "ICE: GenericCreateObject error @@").ToString(), this);
	}
	
}

//This method adds our node to the context menu
void UK2Node_DeConstructObsPayload::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	UClass* Action = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(Action)) {
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		check(Spawner != nullptr);

		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}

void UK2Node_DeConstructObsPayload::SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const
{
	MutatablePin.PinToolTip = UEdGraphSchema_K2::TypeToText(MutatablePin.PinType).ToString();

	UEdGraphSchema_K2 const* const K2Schema = Cast<const UEdGraphSchema_K2>(GetSchema());
	if (K2Schema != nullptr)
	{
		MutatablePin.PinToolTip += TEXT(" ");
		MutatablePin.PinToolTip += K2Schema->GetPinDisplayName(&MutatablePin).ToString();
	}

	MutatablePin.PinToolTip += FString(TEXT("\n")) + PinDescription.ToString();
}

void UK2Node_DeConstructObsPayload::OnClassPinChanged()
{
	// Remove all pins related to archetype variables
	TArray<UEdGraphPin*> OldPins = Pins;
	TArray<UEdGraphPin*> OldClassPins;

	for (UEdGraphPin* OldPin : OldPins)
	{
		if (IsSpawnVarPin(OldPin))
		{
			Pins.Remove(OldPin);
			OldClassPins.Add(OldPin);
		}
	}

	TArray<UEdGraphPin*> NewClassPins;
	if (UClass* UseSpawnClass = GetClassToSpawn())
	{
		CreatePinsForClass(UseSpawnClass, &NewClassPins);
	}

	RestoreSplitPins(OldPins);

	UEdGraphPin* ResultPin = GetResultPin();
	// Cache all the pin connections to the ResultPin, we will attempt to recreate them
	TArray<UEdGraphPin*> ResultPinConnectionList = ResultPin->LinkedTo;
	// Because the archetype has changed, we break the output link as the output pin type will change
	ResultPin->BreakAllPinLinks(true);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Recreate any pin links to the Result pin that are still valid
	for (UEdGraphPin* Connections : ResultPinConnectionList)
	{
		K2Schema->TryCreateConnection(ResultPin, Connections);
	}

	// Rewire the old pins to the new pins so connections are maintained if possible
	RewireOldPinsToNewPins(OldClassPins, Pins, nullptr);

	// Refresh the UI for the graph so the pin changes show up
	GetGraph()->NotifyGraphChanged();

	// Mark dirty
	FBlueprintEditorUtils::MarkBlueprintAsModified(GetBlueprint());
}

UClass* UK2Node_DeConstructObsPayload::GetClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch /*= NULL*/) const
{
	UClass* UseSpawnClass = nullptr;
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;

	UEdGraphPin* ClassPin = GetClassPin(PinsToSearch);
	if (ClassPin && ClassPin->DefaultObject && ClassPin->LinkedTo.Num() == 0)
	{
		UseSpawnClass = CastChecked<UClass>(ClassPin->DefaultObject);
	}
	else if (ClassPin && ClassPin->LinkedTo.Num())
	{
		UEdGraphPin* ClassSource = ClassPin->LinkedTo[0];
		UseSpawnClass = ClassSource ? Cast<UClass>(ClassSource->PinType.PinSubCategoryObject.Get()) : nullptr;
	}

	return UseSpawnClass;
}

UEdGraphPin* UK2Node_DeConstructObsPayload::GetClassPin(const TArray<UEdGraphPin*>* InPinsToSearch /*= NULL*/) const
{
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;

	UEdGraphPin* Pin = nullptr;
	for (UEdGraphPin* TestPin : *PinsToSearch)
	{
		if (TestPin && TestPin->PinName == FDeConstGetPinName::GetPayloadClassTextPin())
		{
			Pin = TestPin;
			break;
		}
	}
	check(Pin == nullptr || Pin->Direction == EGPD_Input);
	return Pin;
}

UEdGraphPin* UK2Node_DeConstructObsPayload::GetEventPin(const TArray<UEdGraphPin*>* InPinsToSearch /*= NULL*/) const
{
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;

	UEdGraphPin* Pin = nullptr;
	for (UEdGraphPin* TestPin : *PinsToSearch)
	{
		if (TestPin && TestPin->PinName == FDeConstGetPinName::GetPayloadInstanceTextPin())
		{
			Pin = TestPin;
			break;
		}
	}
	check(Pin == nullptr || Pin->Direction == EGPD_Input);
	return Pin;
}

UEdGraphPin* UK2Node_DeConstructObsPayload::GetWorldContextPin() const
{
	UEdGraphPin* Pin = FindPin(FDeConstGetPinName::GetWorldContextTextPin());
	check(Pin == nullptr || Pin->Direction == EGPD_Input);
	return Pin;
}

UEdGraphPin* UK2Node_DeConstructObsPayload::GetThenPin() const
{
	UEdGraphPin* Pin = FindPin(UEdGraphSchema_K2::PN_Then);
	check(Pin == nullptr || Pin->Direction == EGPD_Output); // If pin exists, it must be output
	return Pin;
}

UEdGraphPin* UK2Node_DeConstructObsPayload::GetResultPin() const
{
	UEdGraphPin* Pin = FindPinChecked(UEdGraphSchema_K2::PN_ReturnValue);
	check(Pin->Direction == EGPD_Output);
	return Pin;
}

bool UK2Node_DeConstructObsPayload::IsSpawnVarPin(UEdGraphPin* Pin) const
{
	return(Pin->PinName != UEdGraphSchema_K2::PN_Execute &&
		Pin->PinName != UEdGraphSchema_K2::PN_Then &&
		Pin->PinName != UEdGraphSchema_K2::PN_ReturnValue &&
		Pin->PinName != FDeConstGetPinName::GetPayloadClassTextPin() &&
		Pin->PinName != FDeConstGetPinName::GetWorldContextTextPin() &&
		Pin->PinName != FDeConstGetPinName::GetPayloadInstanceTextPin());
}

void UK2Node_DeConstructObsPayload::CreatePinsForClass(UClass* InClass, TArray<UEdGraphPin*>* OutClassPins /*= nullptr*/)
{
	check(InClass);

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	const UObject* const ClassDefaultObject = InClass->GetDefaultObject(false);

	for (TFieldIterator<UProperty> PropertyIt(InClass, EFieldIteratorFlags::IncludeSuper); PropertyIt; ++PropertyIt)
	{
		UProperty* Property = *PropertyIt;
		UClass* PropertyClass = CastChecked<UClass>(Property->GetOuter());
		const bool bIsDelegate = Property->IsA(UMulticastDelegateProperty::StaticClass());
		const bool bIsExposedToSpawn = UEdGraphSchema_K2::IsPropertyExposedOnSpawn(Property);
		const bool bIsSettableExternally = !Property->HasAnyPropertyFlags(CPF_DisableEditOnInstance);

		if (bIsExposedToSpawn &&
			!Property->HasAnyPropertyFlags(CPF_Parm) &&
			bIsSettableExternally &&
			Property->HasAllPropertyFlags(CPF_BlueprintVisible) &&
			!bIsDelegate &&
			(nullptr == FindPin(Property->GetFName())) &&
			FBlueprintEditorUtils::PropertyStillExists(Property))
		{
			if (UEdGraphPin* Pin = CreatePin(EGPD_Output, NAME_None, Property->GetFName()))
			{
				K2Schema->ConvertPropertyToPinType(Property, /*out*/ Pin->PinType);
				if (OutClassPins)
				{
					OutClassPins->Add(Pin);
				}

				if (ClassDefaultObject && K2Schema->PinDefaultValueIsEditable(*Pin))
				{
					FString DefaultValueAsString;
					const bool bDefaultValueSet = FBlueprintEditorUtils::PropertyValueToString(Property, reinterpret_cast<const uint8*>(ClassDefaultObject), DefaultValueAsString);
					check(bDefaultValueSet);
					K2Schema->SetPinAutogeneratedDefaultValue(Pin, DefaultValueAsString);
				}

				// Copy tooltip from the property.
				K2Schema->ConstructBasicPinTooltip(*Pin, Property->GetToolTipText(), Pin->PinToolTip);
			}
		}
	}

	// Change class of output pin
	UEdGraphPin* ResultPin = GetResultPin();
	ResultPin->PinType.PinSubCategoryObject = InClass->GetAuthoritativeClass();
}


#undef LOCTEXT_NAMESPACE