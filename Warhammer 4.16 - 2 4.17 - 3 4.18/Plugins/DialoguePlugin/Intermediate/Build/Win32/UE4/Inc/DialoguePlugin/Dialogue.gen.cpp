// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Classes/Dialogue.h"
PRAGMA_DISABLE_OPTIMIZATION
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
	DIALOGUEPLUGIN_API UFunction* Z_Construct_UFunction_UDialogue_CallFunctionByName();
	DIALOGUEPLUGIN_API UClass* Z_Construct_UClass_UDialogue();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
	DIALOGUEPLUGIN_API UFunction* Z_Construct_UFunction_UDialogue_GetFirstNode();
	DIALOGUEPLUGIN_API UFunction* Z_Construct_UFunction_UDialogue_GetNextNodes();
	DIALOGUEPLUGIN_API UClass* Z_Construct_UClass_UDialogue_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
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
		UPackage* Outer = Z_Construct_UPackage__Script_DialoguePlugin();
		extern uint32 Get_Z_Construct_UScriptStruct_FDialogueNode_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("DialogueNode"), sizeof(FDialogueNode), Get_Z_Construct_UScriptStruct_FDialogueNode_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("DialogueNode"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FDialogueNode>, EStructFlags(0x00000001));
			UProperty* NewProp_DialogueWave = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("DialogueWave"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(DialogueWave, FDialogueNode), 0x0010000000000005, Z_Construct_UClass_UDialogueWave_NoRegister());
			UProperty* NewProp_Sound = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Sound"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(Sound, FDialogueNode), 0x0010000000000005, Z_Construct_UClass_USoundBase_NoRegister());
			UProperty* NewProp_Conditions = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Conditions"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(Conditions, FDialogueNode), 0x0010000000000005, Z_Construct_UScriptStruct_FDialogueConditions());
			UProperty* NewProp_Events = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Events"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(Events, FDialogueNode), 0x0010000000000005, Z_Construct_UScriptStruct_FDialogueEvents());
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(bHasConditions, FDialogueNode);
			UProperty* NewProp_bHasConditions = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("bHasConditions"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(bHasConditions, FDialogueNode), 0x0010000000000005, CPP_BOOL_PROPERTY_BITMASK(bHasConditions, FDialogueNode), sizeof(bool), true);
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(bHasEvents, FDialogueNode);
			UProperty* NewProp_bHasEvents = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("bHasEvents"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(bHasEvents, FDialogueNode), 0x0010000000000005, CPP_BOOL_PROPERTY_BITMASK(bHasEvents, FDialogueNode), sizeof(bool), true);
			UProperty* NewProp_Coordinates = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Coordinates"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(Coordinates, FDialogueNode), 0x0010000000000005, Z_Construct_UScriptStruct_FVector2D());
			UProperty* NewProp_Links = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Links"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(Links, FDialogueNode), 0x0010000000000005);
			UProperty* NewProp_Links_Inner = new(EC_InternalUseOnlyConstructor, NewProp_Links, TEXT("Links"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000);
			UProperty* NewProp_Text = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Text"), RF_Public|RF_Transient|RF_MarkAsNative) UTextProperty(CPP_PROPERTY_BASE(Text, FDialogueNode), 0x0010000000000005);
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(isPlayer, FDialogueNode);
			UProperty* NewProp_isPlayer = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("isPlayer"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(isPlayer, FDialogueNode), 0x0010000000000005, CPP_BOOL_PROPERTY_BITMASK(isPlayer, FDialogueNode), sizeof(bool), true);
			UProperty* NewProp_id = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("id"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(id, FDialogueNode), 0x0010000000000005);
			ReturnStruct->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("IsBlueprintBase"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_DialogueWave, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_DialogueWave, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_Sound, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_Sound, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_Conditions, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_Conditions, TEXT("EditCondition"), TEXT("bHasConditions"));
			MetaData->SetValue(NewProp_Conditions, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_Events, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_Events, TEXT("EditCondition"), TEXT("bHasEvents"));
			MetaData->SetValue(NewProp_Events, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_bHasConditions, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_bHasConditions, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_bHasEvents, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_bHasEvents, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_Coordinates, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_Coordinates, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_Links, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_Links, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_Text, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_Text, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_isPlayer, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_isPlayer, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(NewProp_id, TEXT("Category"), TEXT("Dialogue Node"));
			MetaData->SetValue(NewProp_id, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FDialogueNode_CRC() { return 885770046U; }
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
		UPackage* Outer = Z_Construct_UPackage__Script_DialoguePlugin();
		extern uint32 Get_Z_Construct_UScriptStruct_FDialogueConditions_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("DialogueConditions"), sizeof(FDialogueConditions), Get_Z_Construct_UScriptStruct_FDialogueConditions_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("DialogueConditions"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FDialogueConditions>, EStructFlags(0x00000001));
			UProperty* NewProp_Money = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Money"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(Money, FDialogueConditions), 0x0010000000000005);
			ReturnStruct->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("IsBlueprintBase"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(ReturnStruct, TEXT("ToolTip"), TEXT("add any fields you want here, for example:\nint32 level - to check for minimum level\nitem - to check for inventory item"));
			MetaData->SetValue(NewProp_Money, TEXT("Category"), TEXT("Dialogue Condition"));
			MetaData->SetValue(NewProp_Money, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FDialogueConditions_CRC() { return 3244318702U; }
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
		UPackage* Outer = Z_Construct_UPackage__Script_DialoguePlugin();
		extern uint32 Get_Z_Construct_UScriptStruct_FDialogueEvents_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("DialogueEvents"), sizeof(FDialogueEvents), Get_Z_Construct_UScriptStruct_FDialogueEvents_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("DialogueEvents"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FDialogueEvents>, EStructFlags(0x00000001));
			UProperty* NewProp_AnimationMontage = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("AnimationMontage"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(AnimationMontage, FDialogueEvents), 0x0010000000000005, Z_Construct_UClass_UAnimMontage_NoRegister());
			ReturnStruct->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("IsBlueprintBase"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
			MetaData->SetValue(ReturnStruct, TEXT("ToolTip"), TEXT("add any fields you want here, for example:\n item - to grant/remove item\n actor class - to spawn an actor\n int32 money/experience - to grant money/experience"));
			MetaData->SetValue(NewProp_AnimationMontage, TEXT("Category"), TEXT("Dialogue Event"));
			MetaData->SetValue(NewProp_AnimationMontage, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FDialogueEvents_CRC() { return 2421026865U; }
	void UDialogue::StaticRegisterNativesUDialogue()
	{
		UClass* Class = UDialogue::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "CallFunctionByName", (Native)&UDialogue::execCallFunctionByName },
			{ "GetFirstNode", (Native)&UDialogue::execGetFirstNode },
			{ "GetNextNodes", (Native)&UDialogue::execGetNextNodes },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, ARRAY_COUNT(AnsiFuncs));
	}
	UFunction* Z_Construct_UFunction_UDialogue_CallFunctionByName()
	{
		struct Dialogue_eventCallFunctionByName_Parms
		{
			UObject* Object;
			FString FunctionName;
		};
		UObject* Outer = Z_Construct_UClass_UDialogue();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("CallFunctionByName"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04022401, 65535, sizeof(Dialogue_eventCallFunctionByName_Parms));
			UProperty* NewProp_FunctionName = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("FunctionName"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(FunctionName, Dialogue_eventCallFunctionByName_Parms), 0x0010000000000080);
			UProperty* NewProp_Object = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("Object"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(Object, Dialogue_eventCallFunctionByName_Parms), 0x0010000000000080, Z_Construct_UClass_UObject_NoRegister());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Dialogue"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UDialogue_GetFirstNode()
	{
		struct Dialogue_eventGetFirstNode_Parms
		{
			FDialogueNode ReturnValue;
		};
		UObject* Outer = Z_Construct_UClass_UDialogue();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetFirstNode"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535, sizeof(Dialogue_eventGetFirstNode_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(ReturnValue, Dialogue_eventGetFirstNode_Parms), 0x0010000000000580, Z_Construct_UScriptStruct_FDialogueNode());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Dialogue"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
#endif
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
		UObject* Outer = Z_Construct_UClass_UDialogue();
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetNextNodes"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), nullptr, (EFunctionFlags)0x04020401, 65535, sizeof(Dialogue_eventGetNextNodes_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(ReturnValue, Dialogue_eventGetNextNodes_Parms), 0x0010000000000580);
			UProperty* NewProp_ReturnValue_Inner = new(EC_InternalUseOnlyConstructor, NewProp_ReturnValue, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000, Z_Construct_UScriptStruct_FDialogueNode());
			UProperty* NewProp_Node = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("Node"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(Node, Dialogue_eventGetNextNodes_Parms), 0x0010000000000080, Z_Construct_UScriptStruct_FDialogueNode());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Dialogue"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UDialogue_NoRegister()
	{
		return UDialogue::StaticClass();
	}
	UClass* Z_Construct_UClass_UDialogue()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UDataAsset();
			Z_Construct_UPackage__Script_DialoguePlugin();
			OuterClass = UDialogue::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= (EClassFlags)0x20100080u;

				OuterClass->LinkChild(Z_Construct_UFunction_UDialogue_CallFunctionByName());
				OuterClass->LinkChild(Z_Construct_UFunction_UDialogue_GetFirstNode());
				OuterClass->LinkChild(Z_Construct_UFunction_UDialogue_GetNextNodes());

				UProperty* NewProp_NextNodeId = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("NextNodeId"), RF_Public|RF_Transient|RF_MarkAsNative) UIntProperty(CPP_PROPERTY_BASE(NextNodeId, UDialogue), 0x0010000000000005);
				UProperty* NewProp_Data = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Data"), RF_Public|RF_Transient|RF_MarkAsNative) UArrayProperty(CPP_PROPERTY_BASE(Data, UDialogue), 0x0010000000000015);
				UProperty* NewProp_Data_Inner = new(EC_InternalUseOnlyConstructor, NewProp_Data, TEXT("Data"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(FObjectInitializer(), EC_CppProperty, 0, 0x0000000000000000, Z_Construct_UScriptStruct_FDialogueNode());
				UProperty* NewProp_Name = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Name"), RF_Public|RF_Transient|RF_MarkAsNative) UTextProperty(CPP_PROPERTY_BASE(Name, UDialogue), 0x0010000000000015);
				CPP_BOOL_PROPERTY_BITMASK_STRUCT(DisplayIdleSplines, UDialogue);
				UProperty* NewProp_DisplayIdleSplines = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("DisplayIdleSplines"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(DisplayIdleSplines, UDialogue), 0x0010000000000015, CPP_BOOL_PROPERTY_BITMASK(DisplayIdleSplines, UDialogue), sizeof(bool), true);
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UDialogue_CallFunctionByName(), "CallFunctionByName"); // 3604325050
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UDialogue_GetFirstNode(), "GetFirstNode"); // 2886555865
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UDialogue_GetNextNodes(), "GetNextNodes"); // 2377949743
				static TCppClassTypeInfo<TCppClassTypeTraits<UDialogue> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintType"), TEXT("true"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("Dialogue.h"));
				MetaData->SetValue(OuterClass, TEXT("IsBlueprintBase"), TEXT("true"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
				MetaData->SetValue(OuterClass, TEXT("ObjectInitializerConstructorDeclared"), TEXT(""));
				MetaData->SetValue(NewProp_NextNodeId, TEXT("Category"), TEXT("Dialogue"));
				MetaData->SetValue(NewProp_NextNodeId, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
				MetaData->SetValue(NewProp_NextNodeId, TEXT("ToolTip"), TEXT("don't remove uproperty here"));
				MetaData->SetValue(NewProp_Data, TEXT("Category"), TEXT("Dialogue"));
				MetaData->SetValue(NewProp_Data, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
				MetaData->SetValue(NewProp_Name, TEXT("Category"), TEXT("Dialogue"));
				MetaData->SetValue(NewProp_Name, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
				MetaData->SetValue(NewProp_DisplayIdleSplines, TEXT("Category"), TEXT("Dialogue"));
				MetaData->SetValue(NewProp_DisplayIdleSplines, TEXT("ModuleRelativePath"), TEXT("Classes/Dialogue.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(UDialogue, 2336091909);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UDialogue(Z_Construct_UClass_UDialogue, &UDialogue::StaticClass, TEXT("/Script/DialoguePlugin"), TEXT("UDialogue"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDialogue);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
