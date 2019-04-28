#include "Nodes/K2Node_ConstructObsPayload.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "ObsPayload.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ObsEvent.h"
#include "Misc/AssertionMacros.h"
#include "Kismet/GameplayStatics.h"
#include "UObjectGlobals.h"

#define LOCTEXT_NAMESPACE "K2Node_ConstructObsPayload"

//UK2Node_ConstructObsPayload::UK2Node_ConstructObsPayload(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	NodeTooltip = LOCTEXT("ConstructObsPayloadNodeTooltip", "Create a new payload for an event.");
//}

FText UK2Node_ConstructObsPayload::GetBaseNodeTitle() const
{
	return LOCTEXT("ConstructObsPayload_BaseTitle", "Create ObsPayload");
}

FText UK2Node_ConstructObsPayload::GetNodeTitleFormat() const
{
	return LOCTEXT("ConstructObsPayload", "Create Payload {ClassName}");
}

UClass* UK2Node_ConstructObsPayload::GetClassPinBaseClass() const
{
	return UObsPayload::StaticClass();
}

FText UK2Node_ConstructObsPayload::GetMenuCategory() const
{
	return LOCTEXT("ConstructObsPayloadK2Node_MenuCategory", "ObsEvents");
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
		UEdGraphPin* SpawnOuterPin = GetOuterPin();
		UEdGraphPin* CallOuterPin = CallCreateNode->FindPin(TEXT("Outer"));
		bSucceeded &= SpawnOuterPin && CallOuterPin && CompilerContext.MovePinLinksToIntermediate(*SpawnOuterPin, *CallOuterPin).CanSafeConnect();
	}

	// Connect output actor from 'begin' to 'finish'
	CallCreateNode->GetReturnValuePin()->MakeLinkTo(CallInvokeNode->FindPin(TEXT("payload")));

	// Copy transform connection
	CompilerContext.CopyPinLinksToIntermediate(*CallCreateNode->FindPin(TEXT("Outer")), *CallInvokeNode->FindPin(TEXT("eventToInvoke")));

	CallCreateNode->GetReturnValuePin()->PinType = GetResultPin()->PinType; // Copy type so it uses the right actor subclass
	CompilerContext.MovePinLinksToIntermediate(*GetResultPin(), *CallCreateNode->GetReturnValuePin());

	UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, this, CallCreateNode->GetReturnValuePin(), ClassToSpawn);

	// Make exec connection between 'then' on last node and 'finish'
	LastThen->MakeLinkTo(CallInvokeNode->GetExecPin());

	//UEdGraphPin* CallResultPin = nullptr;
	////connect result
	//{
	//	UEdGraphPin* SpawnResultPin = GetResultPin();
	//	CallResultPin = CallCreateNode->GetReturnValuePin();
	//
	//	// cast HACK. It should be safe. The only problem is native code generation.
	//	if (SpawnResultPin && CallResultPin)
	//	{
	//		CallResultPin->PinType = SpawnResultPin->PinType;
	//	}
	//	bSucceeded &= SpawnResultPin && CallResultPin && CompilerContext.MovePinLinksToIntermediate(*SpawnResultPin, *CallResultPin).CanSafeConnect();
	//}
	//
	////todo: review this
	////assign exposed values and connect then
	//{
	//	UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, this, CallResultPin, ClassToSpawn);
	//	UEdGraphPin* SpawnNodeThen = GetThenPin();
	//	bSucceeded &= SpawnNodeThen && LastThen && CompilerContext.MovePinLinksToIntermediate(*SpawnNodeThen, *LastThen).CanSafeConnect();
	//}

	BreakAllNodeLinks();

	if (!bSucceeded)
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("GenericCreateObject_Error", "ICE: GenericCreateObject error @@").ToString(), this);
	}

	// FINISHED //////////////////////////////////////////////////////////////////////////

	//static const FName BeginSpawningBlueprintFuncName = GET_FUNCTION_NAME_CHECKED(UGameplayStatics, BeginDeferredActorSpawnFromClass);
	//static const FName ActorClassParamName(TEXT("ActorClass"));
	//static const FName WorldContextParamName(TEXT("WorldContextObject"));
	//
	//static const FName FinishSpawningFuncName = GET_FUNCTION_NAME_CHECKED(UGameplayStatics, FinishSpawningActor);
	//static const FName ActorParamName(TEXT("Actor"));
	//static const FName TransformParamName(TEXT("SpawnTransform"));
	//static const FName CollisionHandlingOverrideParamName(TEXT("CollisionHandlingOverride"));
	//static const FName OwnerParamName(TEXT("Owner"));
	//
	//static const FName ObjectParamName(TEXT("Object"));
	//static const FName ValueParamName(TEXT("Value"));
	//static const FName PropertyNameParamName(TEXT("PropertyName"));
	//
	//UK2Node_ConstructObsPayload* SpawnNode = this;
	//UEdGraphPin* SpawnNodeExec = SpawnNode->GetExecPin();
	//UEdGraphPin* SpawnWorldContextPin = SpawnNode->GetWorldContextPin();
	//UEdGraphPin* SpawnClassPin = SpawnNode->GetClassPin();
	//UEdGraphPin* SpawnNodeThen = SpawnNode->GetThenPin();
	//UEdGraphPin* SpawnNodeResult = SpawnNode->GetResultPin();
	//
	////////////////////////////////////////////////////////////////////////////
	//// create 'begin spawn' call node
	//UK2Node_CallFunction* CallBeginSpawnNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(SpawnNode, SourceGraph);
	//CallBeginSpawnNode->FunctionReference.SetExternalMember(BeginSpawningBlueprintFuncName, UGameplayStatics::StaticClass());
	//CallBeginSpawnNode->AllocateDefaultPins();
	//
	//UEdGraphPin* CallBeginExec = CallBeginSpawnNode->GetExecPin();
	//UEdGraphPin* CallBeginWorldContextPin = CallBeginSpawnNode->FindPinChecked(WorldContextParamName);
	//UEdGraphPin* CallBeginActorClassPin = CallBeginSpawnNode->FindPinChecked(ActorClassParamName);
	//UEdGraphPin* CallBeginTransform = CallBeginSpawnNode->FindPinChecked(TransformParamName);
	//UEdGraphPin* CallBeginCollisionHandlingOverride = CallBeginSpawnNode->FindPinChecked(CollisionHandlingOverrideParamName);
	//
	//UEdGraphPin* CallBeginOwnerPin = CallBeginSpawnNode->FindPinChecked(FK2Node_SpawnActorFromClassHelper::OwnerPinName);
	//UEdGraphPin* CallBeginResult = CallBeginSpawnNode->GetReturnValuePin();
	//
	////////////////////////////////////////////////////////////////////////////
	//// create 'finish spawn' call node
	//UK2Node_CallFunction* CallFinishSpawnNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(SpawnNode, SourceGraph);
	//CallFinishSpawnNode->FunctionReference.SetExternalMember(FinishSpawningFuncName, UGameplayStatics::StaticClass());
	//CallFinishSpawnNode->AllocateDefaultPins();
	//
	//UEdGraphPin* CallFinishExec = CallFinishSpawnNode->GetExecPin();
	//UEdGraphPin* CallFinishThen = CallFinishSpawnNode->GetThenPin();
	//UEdGraphPin* CallFinishActor = CallFinishSpawnNode->FindPinChecked(ActorParamName);
	//UEdGraphPin* CallFinishTransform = CallFinishSpawnNode->FindPinChecked(TransformParamName);
	//UEdGraphPin* CallFinishResult = CallFinishSpawnNode->GetReturnValuePin();
	//
	////////////////////////////////////////////////////////////////////////////
	//// create 'set var' nodes
	//
	//// Get 'result' pin from 'begin spawn', this is the actual actor we want to set properties on
	//UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallBeginSpawnNode, SpawnNode, CallBeginResult, ClassToSpawn);
	//
	//// Make exec connection between 'then' on last node and 'finish'
	//LastThen->MakeLinkTo(CallFinishExec);
	//
	//// Break any links to the expanded node
	//SpawnNode->BreakAllNodeLinks();
}

#undef LOCTEXT_NAMESPACE