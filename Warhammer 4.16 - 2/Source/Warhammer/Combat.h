// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Combat.generated.h"

class ANPC_Controller;

/**
 * This class will handle the combat systems for all npcs. 
 */
UCLASS()
class WARHAMMER_API UCombat : public UObject
{
	GENERATED_BODY()
	
public:

	// Sets default values for this pawn's properties
	UCombat();

	/*
	//Starter Combat Function
	static void Attack(ANPC_Controller* npc, ANPC_Controller* enemy);

	ANPC_Controller* char_combat1 = nullptr;
	ANPC_Controller* char_combat2 = nullptr;

	static TArray<ANPC_Controller*> CombatList;
	*/
private:


	
};
