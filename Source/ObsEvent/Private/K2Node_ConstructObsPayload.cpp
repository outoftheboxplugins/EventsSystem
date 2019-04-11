#include "K2Node_ConstructObsPayload.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "ObsPayload.h"
#include "BlueprintEditorUtils.h"
#include "ObsEvent.h"

#define LOCTEXT_NAMESPACE "K2Node_Tutorial"

struct FGetPinName {

	static const FName& GetPayloadClassTextPin() {
		static const FName PayloadClassTextPin(TEXT("Payload data class"));
		return PayloadClassTextPin;
	}

	static const FName& GetEventTextPin() {
		static const FName EventTextPin(TEXT("Event to invoke"));
		return EventTextPin;
	}
};

void UK2Node_ConstructObsPayload::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	//Input
	UEdGraphPin* InPayloadClassPin	= CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Class, UObsPayload::StaticClass(), FGetPinName::GetPayloadClassTextPin());
	UEdGraphPin* InEventPin			= CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObsEvent::StaticClass(), FGetPinName::GetEventTextPin());

	// Output
	UEdGraphPin* ResultPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, UObsPayload::StaticClass(), UEdGraphSchema_K2::PN_ReturnValue);
}

FText UK2Node_ConstructObsPayload::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("ConstructObsPayloadK2Node_Title", "Invoke event with Payload");
}

FText UK2Node_ConstructObsPayload::GetTooltipText() const
{
	return LOCTEXT("ConstructObsPayloadK2Node_Tooltip", "Creats a payload data to invoke an event.");
}

void UK2Node_ConstructObsPayload::GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const
{
	//if (UEdGraphPin* ClassPin = GetClassPin())
	//{
	//	SetPinToolTip(*ClassPin, LOCTEXT("ClassPinDescription", "The object class you want to construct"));
	//}
	//if (UEdGraphPin* ResultPin = GetResultPin())
	//{
	//	SetPinToolTip(*ResultPin, LOCTEXT("ResultPinDescription", "The constructed object"));
	//}
	//if (UEdGraphPin* OuterPin = (UseOuter() ? GetOuterPin() : nullptr))
	//{
	//	SetPinToolTip(*OuterPin, LOCTEXT("OuterPinDescription", "Owner of the constructed object"));
	//}
	//
	return Super::GetPinHoverText(Pin, HoverTextOut);
}

void UK2Node_ConstructObsPayload::PinDefaultValueChanged(UEdGraphPin* Pin)
{
	if (Pin && (Pin->PinName == FGetPinName::GetPayloadClassTextPin()))
	{
		OnClassPinChanged();
	}
}

void UK2Node_ConstructObsPayload::PinConnectionListChanged(UEdGraphPin* Pin)
{
	Super::PinConnectionListChanged(Pin);

	if (Pin && (Pin->PinName == FGetPinName::GetPayloadClassTextPin()))
	{
		OnClassPinChanged();
	}
}

FText UK2Node_ConstructObsPayload::GetMenuCategory() const
{
	return LOCTEXT("ConstructObsPayloadK2Node_MenuCategory", "ObsEvents");
}

void UK2Node_ConstructObsPayload::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
	AllocateDefaultPins();
	if (UClass* UseSpawnClass = GetClassToSpawn(&OldPins))
	{
		CreatePinsForClass(UseSpawnClass);
	}
	RestoreSplitPins(OldPins);
}

//This method adds our node to the context menu
void UK2Node_ConstructObsPayload::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	UClass* Action = GetClass();

	if (ActionRegistrar.IsOpenForRegistration(Action)) {
		UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());
		check(Spawner != nullptr);

		ActionRegistrar.AddBlueprintAction(Action, Spawner);
	}
}

void UK2Node_ConstructObsPayload::SetPinToolTip(UEdGraphPin& MutatablePin, const FText& PinDescription) const
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

void UK2Node_ConstructObsPayload::OnClassPinChanged()
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

UClass* UK2Node_ConstructObsPayload::GetClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch /*= NULL*/) const
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

UEdGraphPin* UK2Node_ConstructObsPayload::GetClassPin(const TArray<UEdGraphPin*>* InPinsToSearch /*= NULL*/) const
{
	const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;

	UEdGraphPin* Pin = nullptr;
	for (UEdGraphPin* TestPin : *PinsToSearch)
	{
		if (TestPin && TestPin->PinName == FGetPinName::GetPayloadClassTextPin())
		{
			Pin = TestPin;
			break;
		}
	}
	check(Pin == nullptr || Pin->Direction == EGPD_Input);
	return Pin;
}

UEdGraphPin* UK2Node_ConstructObsPayload::GetResultPin() const
{
	UEdGraphPin* Pin = FindPinChecked(UEdGraphSchema_K2::PN_ReturnValue);
	check(Pin->Direction == EGPD_Output);
	return Pin;
}

bool UK2Node_ConstructObsPayload::IsSpawnVarPin(UEdGraphPin* Pin) const
{
	return(Pin->PinName != UEdGraphSchema_K2::PN_Execute &&
		Pin->PinName != UEdGraphSchema_K2::PN_Then &&
		Pin->PinName != UEdGraphSchema_K2::PN_ReturnValue &&
		Pin->PinName != FGetPinName::GetPayloadClassTextPin() &&
		Pin->PinName != FGetPinName::GetEventTextPin());
}

void UK2Node_ConstructObsPayload::CreatePinsForClass(UClass* InClass, TArray<UEdGraphPin*>* OutClassPins /*= nullptr*/)
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
			if (UEdGraphPin* Pin = CreatePin(EGPD_Input, NAME_None, Property->GetFName()))
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

	//TODO: Review this.
	// Change class of output pin
	//UEdGraphPin* ResultPin = GetResultPin();
	//ResultPin->PinType.PinSubCategoryObject = InClass->GetAuthoritativeClass();
}

#undef LOCTEXT_NAMESPACE