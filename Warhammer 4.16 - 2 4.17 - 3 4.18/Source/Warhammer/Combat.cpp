// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPC_Controller.h"
#include "Player_Char.h"
#include "Combat.h"

TArray<AActor*> UCombat::CombatList;
bool UCombat::changeStance = false;

UCombat::UCombat()
{
	
}

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
			char1->canAttack = false;
			char2->canAttack = false;

			//Used to choose attack/block animations
			int i = 0;

			//TODO change the 0 below to the weapon variable
			if (char1->GetAnimNum(0) > 1)
			{
				//i needs to change to randrange( 3, char1->attackAnims.Num() - 1) 
				//in order to avoid player's animations

				i = FMath::RandRange(3, (char1->GetAnimNum(0) - 1));
			}
			
			if ((attackRoll1 + char1->attack)  > (attackRoll2 + char2->attack))
			{
				///UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack, their roll was %f and their opponent rolled %f"), *char1->GetName(), (attackRoll1 + char1->attack), (attackRoll2 + char2->attack));

				if ((attackRoll1 + char1->attack) > (defenseRoll2 + char2->attack))
				{
					///UE_LOG(LogTemp, Warning, TEXT("%s hits, their attack roll was %f and their opponent rolled %f"), *char1->GetName(), (attackRoll1 + char1->attack), (defenseRoll2 + char2->attack));

					if (char1->strength >= char2->npcHealth)
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s kills %s at %d"), *char1->GetName(), *char2->GetName(), i);
						//TODO set up death anim for weapons and stances
						char1->CallAttackAnimationEvent(0, i);
						char2->CallDeathAnimationEvent(0, 0);
						char1->attacking = true;

					} else
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s hits %s at %d"), *char1->GetName(), *char2->GetName(), i);
						char1->CallAttackAnimationEvent(0, i);
						char2->CallHitAnimationEvent(0, i);
						char1->attacking = true;
					}
				}  else
				{
					//Here is where we can play the attack and block animations
					///UE_LOG(LogTemp, Warning, TEXT("%s blocks %s at %d"), *char2->GetName(), *char1->GetName(), i - 3);
					char2->CallDefenseAnimationEvent(0, i);
					char1->CallBlockedAnimationEvent(0, i - 3);
					Attack(char1, char2);
				}

			}

			if ((attackRoll1 + char1->attack)  <= (attackRoll2 + char2->attack))
			{
				///UE_LOG(LogTemp, Warning, TEXT("The NPC %s will attack, their roll was %f and their opponent rolled %f"), *char2->GetName(), (attackRoll2 + char2->attack), (attackRoll1 + char1->attack));

				if ((attackRoll2 + char2->attack) > (defenseRoll1 + char1->attack))
				{
					///UE_LOG(LogTemp, Warning, TEXT("%s hits, their attack roll was %f and their opponent rolled %f"), *char2->GetName(), (attackRoll2 + char2->attack), (defenseRoll1 + char1->attack));
					if (char2->strength >= char1->npcHealth)
					{
						//TODO set up death anim for weapons and stances
						///UE_LOG(LogTemp, Warning, TEXT("%s kills %s at %d"), *char1->GetName(), *char2->GetName(), i);
						char2->CallAttackAnimationEvent(0, i);
						char1->CallDeathAnimationEvent(0, 0);
						char2->attacking = true;

					} else
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s hits %s at %d"), *char2->GetName(), *char1->GetName(), i);
						char2->CallAttackAnimationEvent(0, i);
						char1->CallHitAnimationEvent(0, i);
						char2->attacking = true;
					}

				} else
				{
					///UE_LOG(LogTemp, Warning, TEXT("%s blocks %s at %d"), *char1->GetName(), *char2->GetName(), i -3);
					char1->CallDefenseAnimationEvent(0, i);
					char2->CallBlockedAnimationEvent(0, i - 3);
					Attack(char1, char2);
				}
			}
		}

		if (char1->canAttack)
		{
			///UE_LOG(LogTemp, Warning, TEXT("%s damaging the health of %s"), *char1->GetName(), *char2->GetName());
			char2->ModHealth(-char1->strength);
			char1->attacking = false;
		}

		if (char2->canAttack)
		{
			///UE_LOG(LogTemp, Warning, TEXT("%s damaging the health of %s"), *char2->GetName(), *char1->GetName());
			char1->ModHealth(-char2->strength);
			char2->attacking = false;
		}
	}
	//TODO remove npc and enemy from the array once function is finished
}

void UCombat::AttackPlayer(ANPC* npc, APlayer_Char* player)
{
	/*
	if (ensure(npc) && ensure(player))
	{
		AActor* playerChar = Cast<AActor>(player);
		AActor* npcChar = Cast<AActor>(npc);

		if (!CombatList.Contains(npcChar))
		{
			CombatList.Add(npcChar);
			UE_LOG(LogTemp, Warning, TEXT("%s was added to the array"), *npc->GetName());
		}

		if (!CombatList.Contains(playerChar))
		{
			CombatList.Add(playerChar);
			UE_LOG(LogTemp, Warning, TEXT("%s was added to the array"), *playerChar->GetName());
		}

		if (CombatList.Contains(npcChar) && CombatList.Contains(playerChar))
		{
			ANPC* char1 = Cast<ANPC>(CombatList[CombatList.Find(npcChar)]);
			APlayer_Char* char2 = Cast<APlayer_Char>(CombatList[CombatList.Find(playerChar)]);

			float attackRoll1 = FMath::RandRange(0, 10);
			float attackRoll2 = FMath::RandRange(0, 10);
			float defenseRoll1 = FMath::RandRange(0, 10);
			float defenseRoll2 = FMath::RandRange(0, 10);

			//UE_LOG(LogTemp, Warning, TEXT("%s and %s are both in the array"), *char1->GetName(), *char2->GetName());

			if (!char1->attacking && !char2->attacking)
			{
				char1->canAttack = false;
				char2->canAttack = false;

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
						AttackPlayer(char1, char2);
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
						AttackPlayer(char1, char2);
					}
				}
			}

			if (char1->canAttack)
			{
				///UE_LOG(LogTemp, Warning, TEXT("%s damaging the health of %s"), *char1->GetName(), *char2->GetName());
				char2->ModHealth(-char1->strength);
				char1->attacking = false;
			}
			if (char2->canAttack)
			{
				///UE_LOG(LogTemp, Warning, TEXT("%s damaging the health of %s"), *char2->GetName(), *char1->GetName());
				char1->ModHealth(-char2->strength);
				char2->attacking = false;
			}
		}
		//TODO remove npc and enemy from the array once function is finished
	}*/

	if (ensure(npc) && ensure(player))
	{

		FVector distance = player->GetActorLocation() - npc->GetActorLocation();

		//UE_LOG(LogTemp, Warning, TEXT("Attacking the player"));
		if (!npc->attacking)
		{
			npc->attackTimer++;
			npc->canAttack = false;

			if (npc->attackTimer >= 240 && distance.Size() < 190.0f && distance.Size() > 0.0f)
			{
				float rand = FMath::RandRange(0, 10);

				if (rand < 3)
				{
					npc->stance = FMath::RandRange(0, 2);
				}

				npc->CallAttackAnimationEvent(0, npc->stance);
				npc->attacking = true;
				npc->attackTimer = 0;
				UCombat::changeStance = true;
		
				///UE_LOG(LogTemp, Warning, TEXT("Attacking the player at %d"), npc->stance);

			} else if (distance.Size() > 190.0)
			{
				///UE_LOG(LogTemp, Warning, TEXT("resetting timer"));
				npc->attackTimer = 0;

				if (UCombat::changeStance)
				{
					npc->stance = FMath::RandRange(0, 2);
					UCombat::changeStance = false;
				}
			} else if (player->attacking)
			{
				npc->attackTimer = 230;

				if (UCombat::changeStance)
				{
					npc->stance = FMath::RandRange(0, 2);
					UCombat::changeStance = false;
				}
			}
		}

		if (npc->canAttack)
		{
			npc->attacking = false;
		}
		
	}
}



