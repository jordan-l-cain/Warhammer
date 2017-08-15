// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPC_Controller.h"
#include "Player_Char.h"
#include "Combat.h"

TArray<AActor*> UCombat::CombatList;

UCombat::UCombat()
{
	
}

//TODO Solve new issue of npcs targeting someone who targets someone else. One case was an npc was targeting someone who was dead, one was tareting someone who wasn't targeting anyone
void UCombat::Attack(ANPC* npc, ANPC* enemy)
{
	
	if (!ensure(npc) || !ensure(enemy))
	{
		///UE_LOG(LogTemp, Warning, TEXT("The NPC or Enemy is null"));
		return;
	}
	
	if (!CombatList.Contains(npc))
	{
		AActor* char1 = Cast<AActor>(npc);
		CombatList.Add(npc);
		///UE_LOG(LogTemp, Warning, TEXT("%s was added to the array"), *npc->GetName());
	}

	if (CombatList.Contains(npc) && CombatList.Contains(enemy))
	{

		ANPC* char1 = Cast<ANPC>(CombatList[CombatList.Find(npc)]);
		ANPC* char2 = Cast<ANPC>(CombatList[CombatList.Find(enemy)]);

		float attackRoll1 = FMath::RandRange(0, 10);
		float attackRoll2 = FMath::RandRange(0, 10);
		float defenseRoll1 = FMath::RandRange(0, 10);
		float defenseRoll2 = FMath::RandRange(0, 10);
		
		//UE_LOG(LogTemp, Warning, TEXT("%s and %s are both in the array"), *char1->GetName(), *char2->GetName());

		if (!char1->attacking && !char2->attacking)
		{

			if ((attackRoll1 + char1->attack)  > (attackRoll2 + char2->attack))
			{
				///UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack, their roll was %f and their opponent rolled %f"), *char1->GetName(), (attackRoll1 + char1->attack), (attackRoll2 + char2->attack));

				if ((attackRoll1 + char1->attack) > (defenseRoll2 + char2->attack))
				{
					///UE_LOG(LogTemp, Warning, TEXT("%s hits, their attack roll was %f and their opponent rolled %f"), *char1->GetName(), (attackRoll1 + char1->attack), (defenseRoll2 + char2->attack));

					char1->CallAttackAnimationEvent(0);
					char1->attacking = true;
				} else
				{
					//Here is where we can play the attack and block animations
					///UE_LOG(LogTemp, Warning, TEXT("The enemy %s blocked the attack"), *char2->GetName());
				}

			}
			if ((attackRoll1 + char1->attack)  <= (attackRoll2 + char2->attack))
			{
				///UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack, their roll was %f and their opponent rolled %f"), *char2->GetName(), (attackRoll2 + char2->attack), (attackRoll1 + char1->attack));

				if ((attackRoll2 + char2->attack) > (defenseRoll1 + char1->attack))
				{
					///UE_LOG(LogTemp, Warning, TEXT("%s hits, their attack roll was %f and their opponent rolled %f"), *char2->GetName(), (attackRoll2 + char2->attack), (defenseRoll1 + char1->attack));

					char2->CallAttackAnimationEvent(0);
					char2->attacking = true;
				} else
				{
					///UE_LOG(LogTemp, Warning, TEXT("The enemy %s blocked the attack"), *char1->GetName());
				}
			}
		}

		if (char1->GetCanAttack())
		{
			///UE_LOG(LogTemp, Warning, TEXT("%s damaging the health of %s"), *char1->GetName(), *char2->GetName());
			char2->ModHealth(-char1->strength);
			char1->ModCanAttack(false);
			char1->attacking = false;
		}
		if (char2->GetCanAttack())
		{
			///UE_LOG(LogTemp, Warning, TEXT("%s damaging the health of %s"), *char2->GetName(), *char1->GetName());
			char1->ModHealth(-char2->strength);
			char2->ModCanAttack(false);
			char2->attacking = false;
		}
	}
	//TODO remove npc and enemy from the array once function is finished
}

void UCombat::AttackPlayer(ANPC* npc, AActor* player)
{

	if (ensure(npc) && ensure(player))
	{
		
		if (!CombatList.Contains(npc))
		{
			CombatList.Add(npc);
			///UE_LOG(LogTemp, Warning, TEXT("%s was added to the array"), *npc->GetName());
		}

		if (!CombatList.Contains(player))
		{
			CombatList.Add(player);
			///UE_LOG(LogTemp, Warning, TEXT("%s was added to the array"), *npc->GetName());
		}

		if (CombatList.Contains(npc) && CombatList.Contains(player))
		{
			ANPC* char1 = Cast<ANPC>(CombatList[CombatList.Find(npc)]);
			APlayer_Char* char2 = Cast<APlayer_Char>(CombatList[CombatList.Find(player)]);

			//TODO create functions and variables, as well as state, required for combat

			float attackRoll1 = FMath::RandRange(0, 10);
			float attackRoll2 = FMath::RandRange(0, 10);
			float defenseRoll1 = FMath::RandRange(0, 10);
			float defenseRoll2 = FMath::RandRange(0, 10);

			//UE_LOG(LogTemp, Warning, TEXT("%s and %s are both in the array"), *char1->GetName(), *char2->GetName());

			if (!char1->attacking && !char2->attacking)
			{

				if ((attackRoll1 + char1->attack) > (attackRoll2 + char2->attack))
				{
					///UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack, their roll was %f and their opponent rolled %f"), *char1->GetName(), (attackRoll1 + char1->attack), (attackRoll2 + char2->attack));

					if ((attackRoll1 + char1->attack) > (defenseRoll2 + char2->attack))
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s hits, their attack roll was %f and their opponent rolled %f"), *char1->GetName(), (attackRoll1 + char1->attack), (defenseRoll2 + char2->attack));

						char1->CallAttackAnimationEvent(0);
						char1->attacking = true;
					} else
					{
						//Here is where we can play the attack and block animations
						///UE_LOG(LogTemp, Warning, TEXT("The enemy %s blocked the attack"), *char2->GetName());
					}

				}
				if ((attackRoll1 + char1->attack) <= (attackRoll2 + char2->attack))
				{
					///UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack, their roll was %f and their opponent rolled %f"), *char2->GetName(), (attackRoll2 + char2->attack), (attackRoll1 + char1->attack));

					if ((attackRoll2 + char2->attack) > (defenseRoll1 + char1->attack))
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s hits, their attack roll was %f and their opponent rolled %f"), *char2->GetName(), (attackRoll2 + char2->attack), (defenseRoll1 + char1->attack));

						char2->CallAttackAnimationEvent(0);
						char2->attacking = true;
					} else
					{
						///UE_LOG(LogTemp, Warning, TEXT("The enemy %s blocked the attack"), *char1->GetName());
					}
				}
			}

			if (char1->GetCanAttack())
			{
				///UE_LOG(LogTemp, Warning, TEXT("%s damaging the health of %s"), *char1->GetName(), *char2->GetName());
				char2->ModHealth(-char1->strength);
				char1->ModCanAttack(false);
				char1->attacking = false;
			}
			if (char2->GetCanAttack())
			{
				///UE_LOG(LogTemp, Warning, TEXT("%s damaging the health of %s"), *char2->GetName(), *char1->GetName());
				char1->ModHealth(-char2->strength);
				char2->ModCanAttack(false);
				char2->attacking = false;
			}
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("The NPC or Player is null"));
		return;
	}
	//TODO remove npc and enemy from the array once function is finished
}




