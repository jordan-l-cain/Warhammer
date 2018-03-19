// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Combat.generated.h"

class ANPC;
class APlayer_Char;

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

	
	//Starter Combat Function
	static void Attack(ANPC* npc, ANPC* enemy);

	//Player Combat Function
	static void AttackPlayer(ANPC* npc, APlayer_Char* player);

	//Array where all NPCs entering combat will be stored and then detracted after death.
	static TArray<AActor*> CombatList;

	ANPC* char_combat1 = nullptr;
	ANPC* char_combat2 = nullptr;

private:

	static bool changeStance;


	
};
