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
	
	if (!CombatList.Contains(npc))
	{
		CombatList.Add(npc);
		UE_LOG(LogTemp, Warning, TEXT("%s was added to the array"), *npc->GetName());
	}

	if (CombatList.Contains(npc) && CombatList.Contains(enemy))
	{
		ANPC* char1 = CombatList[CombatList.Find(npc)];
		ANPC* char2 = CombatList[CombatList.Find(enemy)];

		float attackRoll1 = FMath::RandRange(0, 10);
		float attackRoll2 = FMath::RandRange(0, 10);
		float defenseRoll1 = FMath::RandRange(0, 10);
		float defenseRoll2 = FMath::RandRange(0, 10);
		
		if (!char1->GetCanAttack() && !char2->GetCanAttack())
		{
			if ((attackRoll1 + char1->attack)  > (attackRoll2 + char2->attack))
			{
				//UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack, their roll was %f and their opponent rolled %f"), *char1->GetName(), (attackRoll1 + char1->attack), (attackRoll2 + char2->attack));

				if ((attackRoll1 + char1->attack) > (defenseRoll2 + char2->attack))
				{
					//UE_LOG(LogTemp, Warning, TEXT("%s hits, their attack roll was %f and their opponent rolled %f"), *char1->GetName(), (attackRoll1 + char1->attack), (defenseRoll2 + char2->attack));

					char1->ModCanAttack(true);
				} else
				{
					//UE_LOG(LogTemp, Warning, TEXT("The enemy %s blocked the attack"), *char2->GetName());
				}
			}

			if ((attackRoll1 + char1->attack)  < (attackRoll2 + char2->attack))
			{
				//UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack, their roll was %f and their opponent rolled %f"), *char2->GetName(), (attackRoll2 + char2->attack), (attackRoll1 + char1->attack));

				if ((attackRoll2 + char2->attack) > (defenseRoll1 + char1->attack))
				{
					//UE_LOG(LogTemp, Warning, TEXT("%s hits, their attack roll was %f and their opponent rolled %f"), *char2->GetName(), (attackRoll2 + char2->attack), (defenseRoll1 + char1->attack));

					char2->ModCanAttack(true);
				} else
				{
					//UE_LOG(LogTemp, Warning, TEXT("The enemy %s blocked the attack"), *char1->GetName());
				}
			}
		}

		if (char1->GetCanAttack())
		{
			char2->ModHealth(-char1->strength);
			char1->ModCanAttack(false);
		}
		if (char2->GetCanAttack())
		{
			char1->ModHealth(-char2->strength);
			char2->ModCanAttack(false);
		}
	}
	//TODO remove npc and enemy from the array once function is finished
}


//TODO NPCs take turns attacking based on bool of canAttack, in future base bool on when animation ends


