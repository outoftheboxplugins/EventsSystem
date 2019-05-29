#include "K2Node_ConstructObsPayload.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "ObsPayload.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ObsEvent.h"
#include "Misc/AssertionMacros.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectGlobals.h"

#define LOCTEXT_NAMESPACE "K2Node_ConstructObsPayload"

struct FGetPinName {
	static const FName& GetEventTextPin() {
		static const FName EventTextPin(TEXT("EventToInvoke"));
		return EventTextPin;
	}
};

//UK2Node_ConstructObsPayload::UK2Node_ConstructObsPayload(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	NodeTooltip = LOCTEXT("ConstructObsPayloadNodeTooltip", "Create a new payload for an event.");
//}

FText UK2Node_ConstructObsPayload::GetBaseNodeTitle() const
{
	return LOCTEXT("ConstructObsPayload_BaseTitle", "Invoke Event with Payload");
}

FText UK2Node_ConstructObsPayload::GetNodeTitleFormat() const
{
	return LOCTEXT("ConstructObsPayload", "Invoke Event with {ClassName}");
}

UClass* UK2Node_ConstructObsPayload::GetClassPinBaseClass() const
{
	return UObsPayload::StaticClass();
}

UEdGraphPin* UK2Node_ConstructObsPayload::GetEventPin() const
{
	UEdGraphPin* Pin = FindPin(FGetPinName::GetEventTextPin());
	ensure(nullptr == Pin || Pin->Direction == EGPD_Input);
	return Pin;
}

FText UK2Node_ConstructObsPayload::GetMenuCategory() const
{
	return LOCTEXT("ConstructObsPayloadK2Node_MenuCategory", "ObsEvents");
}

bool UK2Node_ConstructObsPayload::IsSpawnVarPin(UEdGraphPin* Pin) const
{
	bool eventPinCheck = (Pin->PinName != FGetPinName::GetEventTextPin());
	return eventPinCheck && Super::IsSpawnVarPin(Pin);
}

void UK2Node_ConstructObsPayload::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	UEdGraphPin* ClassPin = GetClassPin();
	if (ClassPin->DefaultObject == NULL)
	{
		ClassPin->DefaultObject = UObsPayload::StaticClass();

		UClass* UseSpawnClass = GetClassToSpawn();
		if (UseSpawnClass != NULL)
		{
			CreatePinsForClass(UseSpawnClass);
		}
	}

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	UEdGraphPin* InEventPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObsEvent::StaticClass(), FGetPinName::GetEventTextPin());

	InEventPin->bAdvancedView = true;
	if (ENodeAdvancedPins::NoPins == AdvancedPinDisplay)
	{
		AdvancedPinDisplay = ENodeAdvancedPins::Hidden;
	}
}

void UK2Node_ConstructObsPayload::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallCreateNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UGameplayStatics, SpawnObject), UGameplayStatics::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	UK2Node_CallFunction* CallInvokeNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallInvokeNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UObsEvent, Invoke), UObsEvent::StaticClass());
	CallInvokeNode->AllocateDefaultPins();

	// store off the class to spawn before we mutate pin connections:
	UClass* ClassToSpawn = GetClassToSpawn();

	bool bSucceeded = true;
	//connect exe
	{
		UEdGraphPin* SpawnExecPin = GetExecPin();
		UEdGraphPin* CallExecPin = CallCreateNode->GetExecPin();
		bSucceeded &= SpawnExecPin && CallExecPin && CompilerContext.MovePinLinksToIntermediate(*SpawnExecPin, *CallExecPin).CanSafeConnect();
	}

	// Move 'then' connection from spawn node to 'finish spawn'
	CompilerContext.MovePinLinksToIntermediate(*GetThenPin(), *CallInvokeNode->GetThenPin());

	//connect class
	{
		UEdGraphPin* SpawnClassPin = GetClassPin();
		UEdGraphPin* CallClassPin = CallCreateNode->FindPin(TEXT("ObjectClass"));
		bSucceeded &= SpawnClassPin && CallClassPin && CompilerContext.MovePinLinksToIntermediate(*SpawnClassPin, *CallClassPin).CanSafeConnect();
	}

	//connect outer
	{
		UEdGraphPin* SpawnOuterPin = GetEventPin();
		UEdGraphPin* CallOuterPin = CallCreateNode->FindPin(TEXT("Outer"));
		bSucceeded &= SpawnOuterPin && CallOuterPin && CompilerContext.MovePinLinksToIntermediate(*SpawnOuterPin, *CallOuterPin).CanSafeConnect();
	}

	// Connect output actor from 'begin' to 'finish'
	CallCreateNode->GetReturnValuePin()->MakeLinkTo(CallInvokeNode->FindPin(TEXT("payload")));

	// Copy transform connection
	CompilerContext.CopyPinLinksToIntermediate(*GetEventPin(), *CallInvokeNode->FindPin(TEXT("eventToInvoke")));

	CallCreateNode->GetReturnValuePin()->PinType = GetResultPin()->PinType; // Copy type so it uses the right actor subclass
	CompilerContext.MovePinLinksToIntermediate(*GetResultPin(), *CallCreateNode->GetReturnValuePin());

	UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, this, CallCreateNode->GetReturnValuePin(), ClassToSpawn);

	// Make exec connection between 'then' on last node and 'finish'
	LastThen->MakeLinkTo(CallInvokeNode->GetExecPin());

	BreakAllNodeLinks();

	if (!bSucceeded)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("GenericCreateObject_Error", "ICE: GenericCreateObject error @@").ToString(), this);
	}
}

FText UK2Node_ConstructObsPayload::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FText superValue = Super::GetNodeTitle(TitleType);
	if (!superValue.CompareTo(FText::FromString("Construct NONE")))
	{
		return  LOCTEXT("ConstructObsPayloadK2Node_NoPayload", "Invoke Event without payload");
	}
	else
	{
		return superValue;
	}
}

#undef LOCTEXT_NAMESPACE