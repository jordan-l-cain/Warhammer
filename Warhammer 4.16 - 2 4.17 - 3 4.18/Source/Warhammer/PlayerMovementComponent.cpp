// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Player_Char.h"
#include "Player_Controller.h"
#include "NPC.h"
#include "NPCMovementComponent.h"
#include "NPC_Controller.h"
#include "PlayerMovementComponent.h"


void UPlayerMovementComponent::MovementState()
{

	//TODO If camera angle to player is greater or lesser than X
		//turn player this way with animation


	if (Enemies.Num() > 0 && !enemyTarget)
	{
		/*
		for (auto* enemy : Enemies)
		{
			if (!enemy->movementComponent->playerTarget)
			{
				FVector distance;
				distance = GetActorLocation() - enemy->GetActorLocation();
				float targetDistanceLength = distance.Size();

				if (enemy->isLeader && targetDistanceLength < 1000.0)
				{
					UE_LOG(LogTemp, Warning, TEXT("%s is enemy leader and within 10 meters."), *enemy->GetName());
					enemy->movementComponent->playerTarget = playerChar;
					enemyTarget = enemy;
					break;

				}else if (targetDistanceLength < 1500.0 && (enemy->movementComponent->curMoveState == enemy->movementComponent->GetMoveToBattleState() || enemy->movementComponent->curMoveState == enemy->movementComponent->GetMoveToLocationState()) && !enemy->movementComponent->enemyTarget)
				{
					
					if (enemy->movementComponent->followTarget)
					{
						if (enemy->movementComponent->battleFollower)
						{
							enemy->movementComponent->followTarget->movementComponent->battleFollower = enemy->movementComponent->battleFollower;
							enemy->movementComponent->battleFollower->movementComponent->followTarget = enemy->movementComponent->followTarget;
							enemy->movementComponent->battleFollower->npcController->MoveToActor(enemy->movementComponent->battleFollower->movementComponent->followTarget);

						} else
						{
							enemy->movementComponent->followTarget = nullptr;
						}
					}

					UE_LOG(LogTemp, Warning, TEXT("%s is within 15 meters"), *enemy->GetName());
					enemy->movementComponent->playerTarget = playerChar;
					enemyTarget = enemy;
					break;
				}
			}
		}
	} else if (enemyTarget)
	{
		for (auto* follower : playerChar->followers)
		{
			if (Enemies.Num() > 0 && !follower->movementComponent->enemyTarget)
			{
				for (auto* enemy : Enemies)
				{
					if (!enemy->movementComponent->enemyTarget && !enemy->movementComponent->playerTarget)
					{
						FVector distance;
						distance = GetActorLocation() - enemy->GetActorLocation();
						float targetDistanceLength = distance.Size();

						if (targetDistanceLength < 1500.0 && (enemy->movementComponent->curMoveState == enemy->movementComponent->GetMoveToBattleState() || enemy->movementComponent->curMoveState == enemy->movementComponent->GetMoveToLocationState()) && !enemy->movementComponent->enemyTarget && !enemy->isLeader)
						{
							if (enemy->movementComponent->followTarget)
							{
								if (enemy->movementComponent->battleFollower)
								{
									enemy->movementComponent->followTarget->movementComponent->battleFollower = enemy->movementComponent->battleFollower;
									enemy->movementComponent->battleFollower->movementComponent->followTarget = enemy->movementComponent->followTarget;
									enemy->movementComponent->battleFollower->npcController->MoveToActor(enemy->movementComponent->battleFollower->movementComponent->followTarget);

								} else
								{
									enemy->movementComponent->followTarget = nullptr;
								}
							}

							UE_LOG(LogTemp, Warning, TEXT("%s is within 15 meters of %s"), *enemy->GetName(), *follower->GetName());
							enemy->movementComponent->enemyTarget = follower;
							follower->movementComponent->enemyTarget = enemy;
							follower->movementComponent->curMoveState = follower->movementComponent->GetMoveToEnemyState();
							follower->npcController->MoveToActor(enemy);
							break;
						}
					}
				}
			}
		}
		

		//TODO disable player movement input
		//playerChar->playerController->MoveToLocation(enemyTarget->GetActorLocation());

		FVector distance;
		distance = GetActorLocation() - enemyTarget->GetActorLocation();
		float targetDistanceLength = distance.Size();

		if (targetDistanceLength <= 190)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is about to be attacked."), *enemyTarget->GetName());

			playerChar->playerController->SetState(playerChar->playerController->GetAttackState());
		}
		*/

		
	} else if(enemyTarget)
	{
		playerChar->playerController->SetState(EPlayerStates::ATTACK);
	}
}

void UPlayerMovementComponent::FilterEnemies(const TArray<AActor*> npcs)
{
	for (auto* enemy : npcs)
	{
		ANPC* actor = Cast<ANPC>(enemy);

		//if npc is a different race, is not dead and does not have an enemy target
		if (ensure(actor) && Enemies.Num() < 2 && ((actor->GetNPCRace() == ANPC::GetDwarfRace()) && (playerChar->GetPlayerRace() == playerChar->GetGreenskinRace()) || (actor->GetNPCRace() == ANPC::GetGreenskinRace()) && (playerChar->GetPlayerRace() == playerChar->GetDwarfRace())) && !actor->isDead && !actor->movementComponent->enemyTarget)
		{
			if (!Enemies.Contains(actor))
			{
				Enemies.Add(actor);
				//TODO solve issue with capsule collider colliding with self's OverlapCollider (capsule collider is set not to generate overlap events)
				UE_LOG(LogTemp, Warning, TEXT("%s was added to %s's array"), *actor->GetName(), *playerChar->GetName());
			}
		} 
	}

	if (Enemies.Num() > 0 && !enemyTarget)
	{
		for (auto* enemy : Enemies)
		{
			if (!enemy->isLeader && enemy->leader && !enemy->movementComponent->playerTarget)
			{
				enemy->leader->FollowersAttack(enemy, playerChar);

			} else if(!enemy->isLeader && !enemy->leader)
			{
				//TODO Do I need to add logic for enemies who don't have a leader?
				UE_LOG(LogTemp, Warning, TEXT("%s does not have a leader, what should the logic be?"), *enemy->GetName());
			}
		}
	}
	
}



