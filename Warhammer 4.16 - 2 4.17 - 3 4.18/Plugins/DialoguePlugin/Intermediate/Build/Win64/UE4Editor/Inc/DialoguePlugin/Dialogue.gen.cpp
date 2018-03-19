// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Classes/Dialogue.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDialogue() {}
// Cross Module References
	DIALOGUEPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FDialogueNode();
	UPackage* Z_Construct_UPackage__Script_DialoguePlugin();
	ENGINE_API UClass* Z_Construct_UClass_UDialogueWave_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USoundBase_NoRegister();
	DIALOGUEPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FDialogueConditions();
	DIALOGUEPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FDialogueEvents();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
	ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
	DIALOGUEPLUGIN_API UClass* Z_Construct_UClass_UDialogue_NoRegister();
	DIALOGUEPLUGIN_API UClass* Z_Construct_UClass_UDialogue();
	ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
	DIALOGUEPLUGIN_API UFunction* Z_Construct_UFunction_UDialogue_CallFunctionByName();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	DIALOGUEPLUGIN_API UFunction* Z_Construct_UFunction_UDialogue_GetFirstNode();
	DIALOGUEPLUGIN_API UFunction* Z_Construct_UFunction_UDialogue_GetNextNodes();
// End Cross Module References
class UScriptStruct* FDialogueNode::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern DIALOGUEPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FDialogueNode_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FDialogueNode, Z_Construct_UPackage__Script_DialoguePlugin(), TEXT("DialogueNode"), sizeof(FDialogueNode), Get_Z_Construct_UScriptStruct_FDialogueNode_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FDialogueNode(FDialogueNode::StaticStruct, TEXT("/Script/DialoguePlugin"), TEXT("DialogueNode"), false, nullptr, nullptr);
static struct FScriptStruct_DialoguePlugin_StaticRegisterNativesFDialogueNode
{
	FScriptStruct_DialoguePlugin_StaticRegisterNativesFDialogueNode()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("DialogueNode")),new UScriptStruct::TCppStructOps<FDialogueNode>);
	}
} ScriptStruct_DialoguePlugin_StaticRegisterNativesFDialogueNode;
	UScriptStruct* Z_Construct_UScriptStruct_FDialogueNode()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FDialogueNode_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_DialoguePlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("DialogueNode"), sizeof(FDialogueNode), Get_Z_Construct_UScriptStruct_FDialogueNode_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "IsBlueprintBase", "true" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDialogueNode>(); };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DialogueWave_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_DialogueWave = { UE4CodeGen_Private::EPropertyClass::Object, "DialogueWave", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueNode, DialogueWave), Z_Construct_UClass_UDialogueWave_NoRegister, METADATA_PARAMS(NewProp_DialogueWave_MetaData, ARRAY_COUNT(NewProp_DialogueWave_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Sound_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Sound = { UE4CodeGen_Private::EPropertyClass::Object, "Sound", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueNode, Sound), Z_Construct_UClass_USoundBase_NoRegister, METADATA_PARAMS(NewProp_Sound_MetaData, ARRAY_COUNT(NewProp_Sound_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Conditions_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "EditCondition", "bHasConditions" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_Conditions = { UE4CodeGen_Private::EPropertyClass::Struct, "Conditions", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueNode, Conditions), Z_Construct_UScriptStruct_FDialogueConditions, METADATA_PARAMS(NewProp_Conditions_MetaData, ARRAY_COUNT(NewProp_Conditions_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Events_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "EditCondition", "bHasEvents" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_Events = { UE4CodeGen_Private::EPropertyClass::Struct, "Events", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueNode, Events), Z_Construct_UScriptStruct_FDialogueEvents, METADATA_PARAMS(NewProp_Events_MetaData, ARRAY_COUNT(NewProp_Events_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bHasConditions_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			auto NewProp_bHasConditions_SetBit = [](void* Obj){ ((FDialogueNode*)Obj)->bHasConditions = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bHasConditions = { UE4CodeGen_Private::EPropertyClass::Bool, "bHasConditions", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(FDialogueNode), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_bHasConditions_SetBit)>::SetBit, METADATA_PARAMS(NewProp_bHasConditions_MetaData, ARRAY_COUNT(NewProp_bHasConditions_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bHasEvents_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			auto NewProp_bHasEvents_SetBit = [](void* Obj){ ((FDialogueNode*)Obj)->bHasEvents = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bHasEvents = { UE4CodeGen_Private::EPropertyClass::Bool, "bHasEvents", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(FDialogueNode), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_bHasEvents_SetBit)>::SetBit, METADATA_PARAMS(NewProp_bHasEvents_MetaData, ARRAY_COUNT(NewProp_bHasEvents_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Coordinates_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_Coordinates = { UE4CodeGen_Private::EPropertyClass::Struct, "Coordinates", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueNode, Coordinates), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(NewProp_Coordinates_MetaData, ARRAY_COUNT(NewProp_Coordinates_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Links_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Links = { UE4CodeGen_Private::EPropertyClass::Array, "Links", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueNode, Links), METADATA_PARAMS(NewProp_Links_MetaData, ARRAY_COUNT(NewProp_Links_MetaData)) };
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_Links_Inner = { UE4CodeGen_Private::EPropertyClass::Int, "Links", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Text_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FTextPropertyParams NewProp_Text = { UE4CodeGen_Private::EPropertyClass::Text, "Text", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueNode, Text), METADATA_PARAMS(NewProp_Text_MetaData, ARRAY_COUNT(NewProp_Text_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_isPlayer_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			auto NewProp_isPlayer_SetBit = [](void* Obj){ ((FDialogueNode*)Obj)->isPlayer = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_isPlayer = { UE4CodeGen_Private::EPropertyClass::Bool, "isPlayer", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(FDialogueNode), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_isPlayer_SetBit)>::SetBit, METADATA_PARAMS(NewProp_isPlayer_MetaData, ARRAY_COUNT(NewProp_isPlayer_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_id_MetaData[] = {
				{ "Category", "Dialogue Node" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_id = { UE4CodeGen_Private::EPropertyClass::Int, "id", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueNode, id), METADATA_PARAMS(NewProp_id_MetaData, ARRAY_COUNT(NewProp_id_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_DialogueWave,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Sound,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Conditions,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Events,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_bHasConditions,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_bHasEvents,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Coordinates,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Links,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Links_Inner,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Text,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_isPlayer,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_id,
			};
			static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
				(UObject* (*)())Z_Construct_UPackage__Script_DialoguePlugin,
				nullptr,
				&UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
				"DialogueNode",
				RF_Public|RF_Transient|RF_MarkAsNative,
				EStructFlags(0x00000001),
				sizeof(FDialogueNode),
				alignof(FDialogueNode),
				PropPointers, ARRAY_COUNT(PropPointers),
				METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FDialogueNode_CRC() { return 2468775783U; }
class UScriptStruct* FDialogueConditions::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern DIALOGUEPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FDialogueConditions_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FDialogueConditions, Z_Construct_UPackage__Script_DialoguePlugin(), TEXT("DialogueConditions"), sizeof(FDialogueConditions), Get_Z_Construct_UScriptStruct_FDialogueConditions_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FDialogueConditions(FDialogueConditions::StaticStruct, TEXT("/Script/DialoguePlugin"), TEXT("DialogueConditions"), false, nullptr, nullptr);
static struct FScriptStruct_DialoguePlugin_StaticRegisterNativesFDialogueConditions
{
	FScriptStruct_DialoguePlugin_StaticRegisterNativesFDialogueConditions()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("DialogueConditions")),new UScriptStruct::TCppStructOps<FDialogueConditions>);
	}
} ScriptStruct_DialoguePlugin_StaticRegisterNativesFDialogueConditions;
	UScriptStruct* Z_Construct_UScriptStruct_FDialogueConditions()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FDialogueConditions_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_DialoguePlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("DialogueConditions"), sizeof(FDialogueConditions), Get_Z_Construct_UScriptStruct_FDialogueConditions_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "IsBlueprintBase", "true" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
				{ "ToolTip", "add any fields you want here, for example:\nint32 level - to check for minimum level\nitem - to check for inventory item" },
			};
#endif
			auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDialogueConditions>(); };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Money_MetaData[] = {
				{ "Category", "Dialogue Condition" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_Money = { UE4CodeGen_Private::EPropertyClass::Int, "Money", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueConditions, Money), METADATA_PARAMS(NewProp_Money_MetaData, ARRAY_COUNT(NewProp_Money_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Money,
			};
			static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
				(UObject* (*)())Z_Construct_UPackage__Script_DialoguePlugin,
				nullptr,
				&UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
				"DialogueConditions",
				RF_Public|RF_Transient|RF_MarkAsNative,
				EStructFlags(0x00000001),
				sizeof(FDialogueConditions),
				alignof(FDialogueConditions),
				PropPointers, ARRAY_COUNT(PropPointers),
				METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FDialogueConditions_CRC() { return 3854279779U; }
class UScriptStruct* FDialogueEvents::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern DIALOGUEPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FDialogueEvents_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FDialogueEvents, Z_Construct_UPackage__Script_DialoguePlugin(), TEXT("DialogueEvents"), sizeof(FDialogueEvents), Get_Z_Construct_UScriptStruct_FDialogueEvents_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FDialogueEvents(FDialogueEvents::StaticStruct, TEXT("/Script/DialoguePlugin"), TEXT("DialogueEvents"), false, nullptr, nullptr);
static struct FScriptStruct_DialoguePlugin_StaticRegisterNativesFDialogueEvents
{
	FScriptStruct_DialoguePlugin_StaticRegisterNativesFDialogueEvents()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("DialogueEvents")),new UScriptStruct::TCppStructOps<FDialogueEvents>);
	}
} ScriptStruct_DialoguePlugin_StaticRegisterNativesFDialogueEvents;
	UScriptStruct* Z_Construct_UScriptStruct_FDialogueEvents()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FDialogueEvents_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_DialoguePlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("DialogueEvents"), sizeof(FDialogueEvents), Get_Z_Construct_UScriptStruct_FDialogueEvents_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "IsBlueprintBase", "true" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
				{ "ToolTip", "add any fields you want here, for example:\n item - to grant/remove item\n actor class - to spawn an actor\n int32 money/experience - to grant money/experience" },
			};
#endif
			auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDialogueEvents>(); };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WorldConditions_MetaData[] = {
				{ "Category", "Global Variables" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
				{ "ToolTip", "TMap of all world conditions that will cause events. Here is the dialogue version which will set the corresponding TMap in the WarhammerGameModeBase" },
			};
#endif
			static const UE4CodeGen_Private::FMapPropertyParams NewProp_WorldConditions = { UE4CodeGen_Private::EPropertyClass::Map, "WorldConditions", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueEvents, WorldConditions), METADATA_PARAMS(NewProp_WorldConditions_MetaData, ARRAY_COUNT(NewProp_WorldConditions_MetaData)) };
			static const UE4CodeGen_Private::FNamePropertyParams NewProp_WorldConditions_Key_KeyProp = { UE4CodeGen_Private::EPropertyClass::Name, "WorldConditions_Key", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000001, 1, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_WorldConditions_ValueProp = { UE4CodeGen_Private::EPropertyClass::Bool, "WorldConditions", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000001, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AnimationMontage_MetaData[] = {
				{ "Category", "Dialogue Event" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AnimationMontage = { UE4CodeGen_Private::EPropertyClass::Object, "AnimationMontage", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(FDialogueEvents, AnimationMontage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(NewProp_AnimationMontage_MetaData, ARRAY_COUNT(NewProp_AnimationMontage_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_WorldConditions,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_WorldConditions_Key_KeyProp,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_WorldConditions_ValueProp,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_AnimationMontage,
			};
			static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
				(UObject* (*)())Z_Construct_UPackage__Script_DialoguePlugin,
				nullptr,
				&UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
				"DialogueEvents",
				RF_Public|RF_Transient|RF_MarkAsNative,
				EStructFlags(0x00000001),
				sizeof(FDialogueEvents),
				alignof(FDialogueEvents),
				PropPointers, ARRAY_COUNT(PropPointers),
				METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FDialogueEvents_CRC() { return 4013846325U; }
	void UDialogue::StaticRegisterNativesUDialogue()
	{
		UClass* Class = UDialogue::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CallFunctionByName", (Native)&UDialogue::execCallFunctionByName },
			{ "GetFirstNode", (Native)&UDialogue::execGetFirstNode },
			{ "GetNextNodes", (Native)&UDialogue::execGetNextNodes },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	UFunction* Z_Construct_UFunction_UDialogue_CallFunctionByName()
	{
		struct Dialogue_eventCallFunctionByName_Parms
		{
			UObject* Object;
			FString FunctionName;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_FunctionName = { UE4CodeGen_Private::EPropertyClass::Str, "FunctionName", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(Dialogue_eventCallFunctionByName_Parms, FunctionName), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Object = { UE4CodeGen_Private::EPropertyClass::Object, "Object", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(Dialogue_eventCallFunctionByName_Parms, Object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_FunctionName,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Object,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Dialogue" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UDialogue, "CallFunctionByName", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(Dialogue_eventCallFunctionByName_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UDialogue_GetFirstNode()
	{
		struct Dialogue_eventGetFirstNode_Parms
		{
			FDialogueNode ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Struct, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(Dialogue_eventGetFirstNode_Parms, ReturnValue), Z_Construct_UScriptStruct_FDialogueNode, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Dialogue" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UDialogue, "GetFirstNode", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(Dialogue_eventGetFirstNode_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UDialogue_GetNextNodes()
	{
		struct Dialogue_eventGetNextNodes_Parms
		{
			FDialogueNode Node;
			TArray<FDialogueNode> ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Array, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(Dialogue_eventGetNextNodes_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FDialogueNode, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_Node = { UE4CodeGen_Private::EPropertyClass::Struct, "Node", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(Dialogue_eventGetNextNodes_Parms, Node), Z_Construct_UScriptStruct_FDialogueNode, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue_Inner,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Node,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Dialogue" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UDialogue, "GetNextNodes", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(Dialogue_eventGetNextNodes_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UDialogue_NoRegister()
	{
		return UDialogue::StaticClass();
	}
	UClass* Z_Construct_UClass_UDialogue()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_UDataAsset,
				(UObject* (*)())Z_Construct_UPackage__Script_DialoguePlugin,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_UDialogue_CallFunctionByName, "CallFunctionByName" }, // 213403178
				{ &Z_Construct_UFunction_UDialogue_GetFirstNode, "GetFirstNode" }, // 2230886570
				{ &Z_Construct_UFunction_UDialogue_GetNextNodes, "GetNextNodes" }, // 1636796028
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "IncludePath", "Dialogue.h" },
				{ "IsBlueprintBase", "true" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
				{ "ObjectInitializerConstructorDeclared", "" },
			};
#endif
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NextNodeId_MetaData[] = {
				{ "Category", "Dialogue" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
				{ "ToolTip", "don't remove uproperty here" },
			};
#endif
			static const UE4CodeGen_Private::FIntPropertyParams NewProp_NextNodeId = { UE4CodeGen_Private::EPropertyClass::Int, "NextNodeId", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(UDialogue, NextNodeId), METADATA_PARAMS(NewProp_NextNodeId_MetaData, ARRAY_COUNT(NewProp_NextNodeId_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[] = {
				{ "Category", "Dialogue" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Data = { UE4CodeGen_Private::EPropertyClass::Array, "Data", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000015, 1, nullptr, STRUCT_OFFSET(UDialogue, Data), METADATA_PARAMS(NewProp_Data_MetaData, ARRAY_COUNT(NewProp_Data_MetaData)) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_Data_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "Data", RF_Public|RF_Transient|RF_MarkAsNative, 0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FDialogueNode, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
				{ "Category", "Dialogue" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			static const UE4CodeGen_Private::FTextPropertyParams NewProp_Name = { UE4CodeGen_Private::EPropertyClass::Text, "Name", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000015, 1, nullptr, STRUCT_OFFSET(UDialogue, Name), METADATA_PARAMS(NewProp_Name_MetaData, ARRAY_COUNT(NewProp_Name_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DisplayIdleSplines_MetaData[] = {
				{ "Category", "Dialogue" },
				{ "ModuleRelativePath", "Classes/Dialogue.h" },
			};
#endif
			auto NewProp_DisplayIdleSplines_SetBit = [](void* Obj){ ((UDialogue*)Obj)->DisplayIdleSplines = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_DisplayIdleSplines = { UE4CodeGen_Private::EPropertyClass::Bool, "DisplayIdleSplines", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000015, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(UDialogue), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_DisplayIdleSplines_SetBit)>::SetBit, METADATA_PARAMS(NewProp_DisplayIdleSplines_MetaData, ARRAY_COUNT(NewProp_DisplayIdleSplines_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_NextNodeId,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Data,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Data_Inner,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Name,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_DisplayIdleSplines,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<UDialogue>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&UDialogue::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00100080u,
				FuncInfo, ARRAY_COUNT(FuncInfo),
				PropPointers, ARRAY_COUNT(PropPointers),
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UDialogue, 108614679);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UDialogue(Z_Construct_UClass_UDialogue, &UDialogue::StaticClass, TEXT("/Script/DialoguePlugin"), TEXT("UDialogue"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDialogue);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
