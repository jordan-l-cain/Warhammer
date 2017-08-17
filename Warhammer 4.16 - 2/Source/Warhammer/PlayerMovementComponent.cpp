// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Player_Char.h"
#include "Player_Controller.h"
#include "NPC.h"
#include "NPCMovementComponent.h"
#include "PlayerMovementComponent.h"


void UPlayerMovementComponent::MovementState()
{
	if (Enemies.Num() > 0 && !enemyTarget)
	{
		for (auto* enemy : Enemies)
		{
			if (!enemy->movementComponent->playerTarget)
			{
				FVector distance;
				distance = GetActorLocation() - enemy->GetActorLocation();
				float targetDistanceLength = distance.Size();

				if (targetDistanceLength < 2500.0 && !enemy->movementComponent->targeted && (enemy->movementComponent->curMoveState == enemy->movementComponent->GetMoveToBattleState() || enemy->movementComponent->curMoveState == enemy->movementComponent->GetMoveToLocationState()) && !enemy->movementComponent->enemyTarget)
				{
					UE_LOG(LogTemp, Warning, TEXT("%s is within 25 meters."), *enemy->GetName());
					enemy->movementComponent->playerTarget = playerChar;
					enemyTarget = enemy;
				}
			}
		}
	} else if (enemyTarget)
	{
		//Move(enemyTarget->GetActorLocation(), 175);

		FVector distance;
		distance = GetActorLocation() - enemyTarget->GetActorLocation();
		float targetDistanceLength = distance.Size();

		if (targetDistanceLength <= 190)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is about to be attacked."), *enemyTarget->GetName());
			playerChar->playerController->SetState(playerChar->playerController->GetAttackState());
		}
	}
}

void UPlayerMovementComponent::FilterEnemies(const TArray<AActor*> npcs)
{
	for (auto* enemy : npcs)
	{
		ANPC* actor = Cast<ANPC>(enemy);

		if (ensure(actor) && ((actor->GetNPCRace() == actor->GetDwarfRace()) && (playerChar->GetPlayerRace() == playerChar->GetGreenskinRace()) || (actor->GetNPCRace() == actor->GetGreenskinRace()) && (playerChar->GetPlayerRace() == playerChar->GetDwarfRace())) && !actor->isDead)
		{
			if (!Enemies.Contains(actor))
			{
				Enemies.Add(Cast<ANPC>(actor));
				//TODO solve issue with capsule collider colliding with self's OverlapCollider (capsule collider is set not to generate overlap events)
				//UE_LOG(LogTemp, Warning, TEXT("%s was added to %s's array"), *actor->GetName(), *playerChar->GetName());
			}
		}
	}
	
}



