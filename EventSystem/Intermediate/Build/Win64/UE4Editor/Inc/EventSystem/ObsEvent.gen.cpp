// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EventSystem/ObsEvent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeObsEvent() {}
// Cross Module References
	EVENTSYSTEM_API UClass* Z_Construct_UClass_UObsEvent_NoRegister();
	EVENTSYSTEM_API UClass* Z_Construct_UClass_UObsEvent();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_EventSystem();
	EVENTSYSTEM_API UFunction* Z_Construct_UFunction_UObsEvent_Invoke();
// End Cross Module References
	void UObsEvent::StaticRegisterNativesUObsEvent()
	{
		UClass* Class = UObsEvent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Invoke", &UObsEvent::execInvoke },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UObsEvent_Invoke_Statics
	{
		struct ObsEvent_eventInvoke_Parms
		{
			UObsEvent* eventToInvoke;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_eventToInvoke;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UObsEvent_Invoke_Statics::NewProp_eventToInvoke = { UE4CodeGen_Private::EPropertyClass::Object, "eventToInvoke", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000080, 1, nullptr, STRUCT_OFFSET(ObsEvent_eventInvoke_Parms, eventToInvoke), Z_Construct_UClass_UObsEvent_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UObsEvent_Invoke_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UObsEvent_Invoke_Statics::NewProp_eventToInvoke,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UObsEvent_Invoke_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ObsEvent.h" },
		{ "ToolTip", "Invoke the event." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UObsEvent_Invoke_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UObsEvent, "Invoke", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(ObsEvent_eventInvoke_Parms), Z_Construct_UFunction_UObsEvent_Invoke_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UObsEvent_Invoke_Statics::PropPointers), 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UObsEvent_Invoke_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UObsEvent_Invoke_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UObsEvent_Invoke()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UObsEvent_Invoke_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UObsEvent_NoRegister()
	{
		return UObsEvent::StaticClass();
	}
	struct Z_Construct_UClass_UObsEvent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UObsEvent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_EventSystem,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UObsEvent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UObsEvent_Invoke, "Invoke" }, // 1833764423
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UObsEvent_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ObsEvent.h" },
		{ "ModuleRelativePath", "ObsEvent.h" },
		{ "ToolTip", "Event holding all the listeners and delegating the call to them." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UObsEvent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UObsEvent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UObsEvent_Statics::ClassParams = {
		&UObsEvent::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x001000A0u,
		FuncInfo, ARRAY_COUNT(FuncInfo),
		nullptr, 0,
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_UObsEvent_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UObsEvent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UObsEvent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UObsEvent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UObsEvent, 3217707034);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UObsEvent(Z_Construct_UClass_UObsEvent, &UObsEvent::StaticClass, TEXT("/Script/EventSystem"), TEXT("UObsEvent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UObsEvent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
