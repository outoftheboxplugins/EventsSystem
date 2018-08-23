// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef EVENTSYSTEM_EventSystemGameModeBase_generated_h
#error "EventSystemGameModeBase.generated.h already included, missing '#pragma once' in EventSystemGameModeBase.h"
#endif
#define EVENTSYSTEM_EventSystemGameModeBase_generated_h

#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_RPC_WRAPPERS
#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEventSystemGameModeBase(); \
	friend struct Z_Construct_UClass_AEventSystemGameModeBase_Statics; \
public: \
	DECLARE_CLASS(AEventSystemGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/EventSystem"), NO_API) \
	DECLARE_SERIALIZER(AEventSystemGameModeBase)


#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAEventSystemGameModeBase(); \
	friend struct Z_Construct_UClass_AEventSystemGameModeBase_Statics; \
public: \
	DECLARE_CLASS(AEventSystemGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/EventSystem"), NO_API) \
	DECLARE_SERIALIZER(AEventSystemGameModeBase)


#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEventSystemGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEventSystemGameModeBase) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEventSystemGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEventSystemGameModeBase); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEventSystemGameModeBase(AEventSystemGameModeBase&&); \
	NO_API AEventSystemGameModeBase(const AEventSystemGameModeBase&); \
public:


#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AEventSystemGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AEventSystemGameModeBase(AEventSystemGameModeBase&&); \
	NO_API AEventSystemGameModeBase(const AEventSystemGameModeBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEventSystemGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEventSystemGameModeBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AEventSystemGameModeBase)


#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET
#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_12_PROLOG
#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_RPC_WRAPPERS \
	EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_INCLASS \
	EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
	EventSystem_Source_EventSystem_EventSystemGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID EventSystem_Source_EventSystem_EventSystemGameModeBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
