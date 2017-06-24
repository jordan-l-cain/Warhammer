// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "AI_Controller.h"
#include "Combat.h"

TArray<AAI_Controller*> UCombat::CombatList;

UCombat::UCombat()
{
	
}

void UCombat::Attack(AAI_Controller* character, AAI_Controller* enemy)
{
	if (!ensure(character) || !ensure(enemy))
	{
		UE_LOG(LogTemp, Warning, TEXT("The Character or Enemy is null"));
		return;
	}
	
	float randomNumber = FMath::RandRange(0, 2);
	
	if (!CombatList.Contains(character))
	{
		CombatList.Add(character);
		UE_LOG(LogTemp, Warning, TEXT("%s was added to the array"), *character->GetName());
	}

	if (CombatList.Contains(character) && CombatList.Contains(enemy))
	{
		AAI_Controller* char1 = CombatList[CombatList.Find(character)];
		AAI_Controller* char2 = CombatList[CombatList.Find(enemy)];
	
		//TODO add bool restraint so that characters can only roll once the other is done attacking
		
		if (!char1->GetCanAttack() && !char2->GetCanAttack())
		{
			if (randomNumber > 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("The Character %s will attack"), *character->GetName());
				char1->ModCanAttack(true);
			}

			if (randomNumber <= 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("The Character %s will attack"), *enemy->GetName());
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


//TODO make whether a character dependent on whether their opponent is now attacking, character not attcking should be on standby until enemy finishes their roll


