// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "Combat.h"

TArray<ANPC*> UCombat::CombatList;

UCombat::UCombat()
{
	
}

void UCombat::Attack(ANPC* npc, ANPC* enemy)
{
	
	if (!ensure(npc) || !ensure(enemy))
	{
		UE_LOG(LogTemp, Warning, TEXT("The NPC or Enemy is null"));
		return;
	}
	
	float randomNumber = FMath::RandRange(0, 2);
	
	if (!CombatList.Contains(npc))
	{
		CombatList.Add(npc);
		UE_LOG(LogTemp, Warning, TEXT("%s was added to the array"), *npc->GetName());
	}

	if (CombatList.Contains(npc) && CombatList.Contains(enemy))
	{
		ANPC* char1 = CombatList[CombatList.Find(npc)];
		ANPC* char2 = CombatList[CombatList.Find(enemy)];
		
		if (!char1->GetCanAttack() && !char2->GetCanAttack())
		{
			if (randomNumber > 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack"), *npc->GetName());
				char1->ModCanAttack(true);
			}

			if (randomNumber <= 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack"), *enemy->GetName());
				char2->ModCanAttack(true);
			}
		}

		if (char1->GetCanAttack())
		{
			char2->ModHealth(-1);
			char1->ModCanAttack(false);
		}
		if (char2->GetCanAttack())
		{
			char1->ModHealth(-1);
			char2->ModCanAttack(false);
		}
	}
	
}

//TODO NPCs take turns attacking based on bool of canAttack, in future base bool on when animation ends


