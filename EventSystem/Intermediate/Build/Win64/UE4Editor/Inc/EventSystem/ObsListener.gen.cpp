// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EventSystem/ObsListener.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeObsListener() {}
// Cross Module References
	EVENTSYSTEM_API UClass* Z_Construct_UClass_UObsListener_NoRegister();
	EVENTSYSTEM_API UClass* Z_Construct_UClass_UObsListener();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	UPackage* Z_Construct_UPackage__Script_EventSystem();
	EVENTSYSTEM_API UClass* Z_Construct_UClass_UObsEvent_NoRegister();
// End Cross Module References
	void UObsListener::StaticRegisterNativesUObsListener()
	{
	}
	UClass* Z_Construct_UClass_UObsListener_NoRegister()
	{
		return UObsListener::StaticClass();
	}
	struct Z_Construct_UClass_UObsListener_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_eventToListen_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_eventToListen;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UObsListener_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_EventSystem,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UObsListener_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "ObsListener.h" },
		{ "ModuleRelativePath", "ObsListener.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UObsListener_Statics::NewProp_eventToListen_MetaData[] = {
		{ "Category", "Observer Events" },
		{ "ModuleRelativePath", "ObsListener.h" },
		{ "ToolTip", "Event to listen to." },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UObsListener_Statics::NewProp_eventToListen = { UE4CodeGen_Private::EPropertyClass::Object, "eventToListen", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000801, 1, nullptr, STRUCT_OFFSET(UObsListener, eventToListen), Z_Construct_UClass_UObsEvent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UObsListener_Statics::NewProp_eventToListen_MetaData, ARRAY_COUNT(Z_Construct_UClass_UObsListener_Statics::NewProp_eventToListen_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UObsListener_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UObsListener_Statics::NewProp_eventToListen,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UObsListener_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UObsListener>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UObsListener_Statics::ClassParams = {
		&UObsListener::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x00B000A0u,
		nullptr, 0,
		Z_Construct_UClass_UObsListener_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_UObsListener_Statics::PropPointers),
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_UObsListener_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UObsListener_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UObsListener()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UObsListener_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UObsListener, 3670997714);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UObsListener(Z_Construct_UClass_UObsListener, &UObsListener::StaticClass, TEXT("/Script/EventSystem"), TEXT("UObsListener"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UObsListener);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
