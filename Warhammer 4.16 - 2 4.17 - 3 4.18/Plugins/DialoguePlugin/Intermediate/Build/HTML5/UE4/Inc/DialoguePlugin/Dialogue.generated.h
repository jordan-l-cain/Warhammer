// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
struct FDialogueNode;
#ifdef DIALOGUEPLUGIN_Dialogue_generated_h
#error "Dialogue.generated.h already included, missing '#pragma once' in Dialogue.h"
#endif
#define DIALOGUEPLUGIN_Dialogue_generated_h

#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_33_GENERATED_BODY \
	friend DIALOGUEPLUGIN_API class UScriptStruct* Z_Construct_UScriptStruct_FDialogueNode(); \
	DIALOGUEPLUGIN_API static class UScriptStruct* StaticStruct();


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_27_GENERATED_BODY \
	friend DIALOGUEPLUGIN_API class UScriptStruct* Z_Construct_UScriptStruct_FDialogueConditions(); \
	DIALOGUEPLUGIN_API static class UScriptStruct* StaticStruct();


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_15_GENERATED_BODY \
	friend DIALOGUEPLUGIN_API class UScriptStruct* Z_Construct_UScriptStruct_FDialogueEvents(); \
	DIALOGUEPLUGIN_API static class UScriptStruct* StaticStruct();


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execCallFunctionByName) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_Object); \
		P_GET_PROPERTY(UStrProperty,Z_Param_FunctionName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UDialogue::CallFunctionByName(Z_Param_Object,Z_Param_FunctionName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetNextNodes) \
	{ \
		P_GET_STRUCT(FDialogueNode,Z_Param_Node); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(TArray<FDialogueNode>*)Z_Param__Result=this->GetNextNodes(Z_Param_Node); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFirstNode) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FDialogueNode*)Z_Param__Result=this->GetFirstNode(); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execCallFunctionByName) \
	{ \
		P_GET_OBJECT(UObject,Z_Param_Object); \
		P_GET_PROPERTY(UStrProperty,Z_Param_FunctionName); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UDialogue::CallFunctionByName(Z_Param_Object,Z_Param_FunctionName); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetNextNodes) \
	{ \
		P_GET_STRUCT(FDialogueNode,Z_Param_Node); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(TArray<FDialogueNode>*)Z_Param__Result=this->GetNextNodes(Z_Param_Node); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFirstNode) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FDialogueNode*)Z_Param__Result=this->GetFirstNode(); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUDialogue(); \
	friend DIALOGUEPLUGIN_API class UClass* Z_Construct_UClass_UDialogue(); \
public: \
	DECLARE_CLASS(UDialogue, UDataAsset, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/DialoguePlugin"), NO_API) \
	DECLARE_SERIALIZER(UDialogue) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_INCLASS \
private: \
	static void StaticRegisterNativesUDialogue(); \
	friend DIALOGUEPLUGIN_API class UClass* Z_Construct_UClass_UDialogue(); \
public: \
	DECLARE_CLASS(UDialogue, UDataAsset, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/DialoguePlugin"), NO_API) \
	DECLARE_SERIALIZER(UDialogue) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UDialogue(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDialogue) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDialogue); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDialogue); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UDialogue(UDialogue&&); \
	NO_API UDialogue(const UDialogue&); \
public:


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UDialogue(UDialogue&&); \
	NO_API UDialogue(const UDialogue&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDialogue); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDialogue); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UDialogue)


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_69_PROLOG
#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_RPC_WRAPPERS \
	HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_INCLASS \
	HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h_72_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_DialoguePlugin_Source_DialoguePlugin_Classes_Dialogue_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
