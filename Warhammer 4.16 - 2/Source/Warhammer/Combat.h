// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Combat.generated.h"

class AAI_Controller;

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
	static void Attack(AAI_Controller* npc, AAI_Controller* enemy);

	AAI_Controller* char_combat1 = nullptr;
	AAI_Controller* char_combat2 = nullptr;

	static TArray<AAI_Controller*> CombatList;
	*/
private:


	
};
