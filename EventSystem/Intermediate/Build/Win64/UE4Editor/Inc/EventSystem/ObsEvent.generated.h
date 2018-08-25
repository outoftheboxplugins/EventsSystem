// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObsEvent;
#ifdef EVENTSYSTEM_ObsEvent_generated_h
#error "ObsEvent.generated.h already included, missing '#pragma once' in ObsEvent.h"
#endif
#define EVENTSYSTEM_ObsEvent_generated_h

#define EventSystem_Source_EventSystem_ObsEvent_h_17_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execInvoke) \
	{ \
		P_GET_OBJECT(UObsEvent,Z_Param_eventToInvoke); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UObsEvent::Invoke(Z_Param_eventToInvoke); \
		P_NATIVE_END; \
	}


#define EventSystem_Source_EventSystem_ObsEvent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execInvoke) \
	{ \
		P_GET_OBJECT(UObsEvent,Z_Param_eventToInvoke); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UObsEvent::Invoke(Z_Param_eventToInvoke); \
		P_NATIVE_END; \
	}


#define EventSystem_Source_EventSystem_ObsEvent_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUObsEvent(); \
	friend struct Z_Construct_UClass_UObsEvent_Statics; \
public: \
	DECLARE_CLASS(UObsEvent, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/EventSystem"), NO_API) \
	DECLARE_SERIALIZER(UObsEvent)


#define EventSystem_Source_EventSystem_ObsEvent_h_17_INCLASS \
private: \
	static void StaticRegisterNativesUObsEvent(); \
	friend struct Z_Construct_UClass_UObsEvent_Statics; \
public: \
	DECLARE_CLASS(UObsEvent, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/EventSystem"), NO_API) \
	DECLARE_SERIALIZER(UObsEvent)


#define EventSystem_Source_EventSystem_ObsEvent_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UObsEvent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UObsEvent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UObsEvent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UObsEvent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UObsEvent(UObsEvent&&); \
	NO_API UObsEvent(const UObsEvent&); \
public:


#define EventSystem_Source_EventSystem_ObsEvent_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UObsEvent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UObsEvent(UObsEvent&&); \
	NO_API UObsEvent(const UObsEvent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UObsEvent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UObsEvent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UObsEvent)


#define EventSystem_Source_EventSystem_ObsEvent_h_17_PRIVATE_PROPERTY_OFFSET
#define EventSystem_Source_EventSystem_ObsEvent_h_14_PROLOG
#define EventSystem_Source_EventSystem_ObsEvent_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	EventSystem_Source_EventSystem_ObsEvent_h_17_PRIVATE_PROPERTY_OFFSET \
	EventSystem_Source_EventSystem_ObsEvent_h_17_RPC_WRAPPERS \
	EventSystem_Source_EventSystem_ObsEvent_h_17_INCLASS \
	EventSystem_Source_EventSystem_ObsEvent_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define EventSystem_Source_EventSystem_ObsEvent_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	EventSystem_Source_EventSystem_ObsEvent_h_17_PRIVATE_PROPERTY_OFFSET \
	EventSystem_Source_EventSystem_ObsEvent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	EventSystem_Source_EventSystem_ObsEvent_h_17_INCLASS_NO_PURE_DECLS \
	EventSystem_Source_EventSystem_ObsEvent_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID EventSystem_Source_EventSystem_ObsEvent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
