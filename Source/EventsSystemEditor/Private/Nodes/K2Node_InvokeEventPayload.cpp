#include "K2Node_InvokeEventPayload.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "EventsSystemPayload.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Event.h"
#include "Misc/AssertionMacros.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectGlobals.h"

#define LOCTEXT_NAMESPACE "K2Node_InvokeEventPayload"

struct FGetPinName {
	static const FName& GetEventTextPin() {
		static const FName EventTextPin(TEXT("EventToInvoke"));
		return EventTextPin;
	}
};

UK2Node_InvokeEventPayload::UK2Node_InvokeEventPayload(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeTooltip = LOCTEXT("InvokeEventPayloadNodeTooltip", "Create a new payload and invokes an event with it.");
}

FText UK2Node_InvokeEventPayload::GetBaseNodeTitle() const
{
	return LOCTEXT("InvokeEventPayload_BaseTitle", "Invoke Event with Payload");
}

FText UK2Node_InvokeEventPayload::GetNodeTitleFormat() const
{
	return LOCTEXT("InvokeEventPayload", "Invoke Event with {ClassName}");
}

UClass* UK2Node_InvokeEventPayload::GetClassPinBaseClass() const
{
	return UEventsSystemPayload::StaticClass();
}

UEdGraphPin* UK2Node_InvokeEventPayload::GetEventPin() const
{
	UEdGraphPin* Pin = FindPin(FGetPinName::GetEventTextPin());
	ensure(nullptr == Pin || Pin->Direction == EGPD_Input);
	return Pin;
}

FText UK2Node_InvokeEventPayload::GetMenuCategory() const
{
	return LOCTEXT("InvokeEventPayloadK2Node_MenuCategory", "EventsSystem");
}

bool UK2Node_InvokeEventPayload::IsSpawnVarPin(UEdGraphPin* Pin) const
{
	bool eventPinCheck = (Pin->PinName != FGetPinName::GetEventTextPin());
	return eventPinCheck && Super::IsSpawnVarPin(Pin);
}

void UK2Node_InvokeEventPayload::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	UEdGraphPin* ClassPin = GetClassPin();
	if (ClassPin->DefaultObject == NULL)
	{
		ClassPin->DefaultObject = UEventsSystemPayload::StaticClass();

		UClass* UseSpawnClass = GetClassToSpawn();
		if (UseSpawnClass != NULL)
		{
			CreatePinsForClass(UseSpawnClass);
		}
	}

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	UEdGraphPin* InEventPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UEvent::StaticClass(), FGetPinName::GetEventTextPin());

	InEventPin->bAdvancedView = true;
	if (ENodeAdvancedPins::NoPins == AdvancedPinDisplay)
	{
		AdvancedPinDisplay = ENodeAdvancedPins::Hidden;
	}
}

void UK2Node_InvokeEventPayload::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallCreateNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UGameplayStatics, SpawnObject), UGameplayStatics::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	UK2Node_CallFunction* CallInvokeNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	CallInvokeNode->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UEvent, Invoke), UEvent::StaticClass());
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
		//bSucceeded &= SpawnOuterPin && CallOuterPin && CompilerContext.MovePinLinksToIntermediate(*SpawnOuterPin, *CallOuterPin).CanSafeConnect();
        bSucceeded &= SpawnOuterPin && CallOuterPin && CompilerContext.CopyPinLinksToIntermediate(*SpawnOuterPin, *CallOuterPin).CanSafeConnect();
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

FText UK2Node_InvokeEventPayload::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	FText superValue = Super::GetNodeTitle(TitleType);
	if (!superValue.CompareTo(FText::FromString("Construct NONE")))
	{
		return  LOCTEXT("InvokeEventPayloadK2Node_NoPayload", "Invoke Event without payload");
	}
	else
	{
		return superValue;
	}
}

#undef LOCTEXT_NAMESPACE