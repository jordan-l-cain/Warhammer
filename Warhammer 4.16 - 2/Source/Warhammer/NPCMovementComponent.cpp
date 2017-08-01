// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPC_Controller.h"
#include "WarhammerGameModeBase.h"
#include "NPCMovementComponent.h"


void UNPCMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	originalRotation = GetOwner()->GetActorRotation();
}

void UNPCMovementComponent::MoveAI(ANPC* npc)
{
	switch (curMoveState)
	{
		case EMoveStates::MOVETOLOCATION:
			MoveToLocation(npc);
		break;

		case EMoveStates::FOLLOW:
			Follow(npc);
			break;

		case EMoveStates::MOVETOENEMY:
			MoveToEnemy(npc);
			break;

		case EMoveStates::MOVETOBATTLE:
			MoveToBattle(npc);
			break;

		case EMoveStates::NULLMOVE:
			curMoveState = defaultState;
	}

}


void UNPCMovementComponent::MoveToLocation(ANPC* npc)
{
	//We do not have to check for overlapping actors in this movement mode, because no enemies will run around on their own. 
	//Because leaders will be set no matter what, the leader will always have a target if there are enemies in the game.

	//Create alternate movement options for after combat

	///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, trying to move to location."), *npc->GetName());
	MaxWalkSpeed = 600;
	locationTimer++;

	if (!enemyLeader)
	{
		///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, does not have an enemy leader."), *npc->GetName());

		
		moveToLeader = true;

		if (locationTimer >= 20)
		{
			npc->npcController->MoveToActor(npc->waypoint);
			UE_LOG(LogTemp, Warning, TEXT("This npc is %s, about to search for enemy leaders."), *npc->GetName());
			for (auto* actor : AWarhammerGameModeBase::LeaderList)
			{
				///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, has found at least one enemy leader"), *npc->GetName());

				if (npc->GetNPCRace() != actor->GetNPCRace() && !actor->isDead)
				{
					FVector leaderDistance = npc->GetActorLocation() - actor->GetActorLocation();

					if (leaderDistance.Size() <= 20000)
					{
						middlePoint = (npc->GetActorLocation() + actor->GetActorLocation()) / 2;

						for (auto* follower : npc->followers)
						{
							follower->movementComponent->middlePoint = middlePoint;
						}

						enemyLeader = actor;
						//TODO add an alternate way for them to get to each other if the location is not on nav mesh
					}
				}
			}

			locationTimer = 0;
		}

	} else if (enemyLeader)
	{
		///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, has an enemy leader target"), *npc->GetName());

		if (locationTimer >= 20)
		{
			if (ensure(npc) && moveToLeader)
			{
				npc->npcController->MoveToLocation(middlePoint);
				moveToLeader = false;
			}

			FVector distance = npc->GetActorLocation() - enemyLeader->GetActorLocation();

			if (distance.Size() <= 3500)
			{
				setFollowersMoveToEnemy = true;
				curMoveState = EMoveStates::MOVETOBATTLE;
				enemyLeader = nullptr;
				//TODO add an alternate way for them to get to each other if the location is not on nav mesh
			}

			locationTimer = 0;
		}
	}
}

void UNPCMovementComponent::Follow(ANPC* npc)
{
	///UE_LOG(LogTemp, Warning, TEXT("This npc: %s, is trying to follow."), *npc->GetName());
	MaxWalkSpeed = 750;

	timer++;

	if (npc->leader )
	{
		
		if (followerIndex < 4)
		{
			//TODO change y position to multiply by the number of followers.Num() instead of just 300
			FVector formationPosition = FVector( npc->leader->GetActorLocation().X - 10, (npc->leader->GetActorLocation().Y - 300) + (followerIndex * 300), npc->leader->GetActorLocation().Z );
			FVector distanceToPosition = npc->GetActorLocation() - formationPosition;
			MaxWalkSpeed = (distanceToPosition.Size() + npc->leader->movementComponent->Velocity.X) * .35;
			
			if (timer >= 35)
			{
				npc->npcController->MoveToLocation(formationPosition);
				timer = 0;
			}
		}

	} else if(!npc->leader)
	{
		UE_LOG(LogTemp, Warning, TEXT("The common npc does not have a leader"));
	}
}

void UNPCMovementComponent::MoveToBattle(ANPC* npc)
{
	//TODO transition back to their respectable states
	//TODO fix move to enemy/combat
	///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, entering move to enemy state."), *npc->GetName());

	if (!enemiesAreDead)
	{
		moveToEnemyTimer++;

		if (moveToEnemyTimer > 120)
		{
			npc->npcController->MoveToLocation(middlePoint);
			moveToEnemyTimer = 0;
		}

		if (npc->isLeader)
		{
			MaxWalkSpeed = 400;

			if (setFollowersMoveToEnemy)
			{
				for (auto* follower : npc->followers)
				{
					///Need to be made to call only once per combat
					UE_LOG(LogTemp, Warning, TEXT("Setting %s to move to battle state"), *follower->GetName());
					if (follower->movementComponent->curMoveState != follower->movementComponent->GetMoveToBattleState())
					{
						follower->movementComponent->curMoveState = follower->movementComponent->GetMoveToBattleState();
					}
				}

				setFollowersMoveToEnemy = false;
			}
		} else if (npc->leader)
		{
			MaxWalkSpeed = npc->leader->movementComponent->MaxWalkSpeed * 1.5;
		}

		//TODO optimize for large numbers, Only add npc's to array, and only up to 5? Need way to remove when they're dead as well

		//If the npc has not yet seen an enemy, continue moving towards middle of battle.
		//This is here to prevent followers in the back of a formation from calling a new leader.
		//Once they have a target, the npc will switch to the MoveToEnemy state.
		if (hasSeenEnemy && !enemyTarget)
		{

			if (otherChars.Num() > 0)
			{
				TArray<ANPC*> deadChars;

				for (auto* otherChar : otherChars)
				{
					//TODO Logic for finding an enemy isn't working. NPC was able to target an NPC who already had a target. A targeted B, B targeted no one, and C targeted A.
					///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, comparing overlapping actor %s."), *npc->GetName(), *otherChar->GetName());
					if (!otherChar->isDead)
					{
						///Find distance between this ai and each enemy in the overlapping actors array
						FVector distance;
						distance = npc->GetActorLocation() - otherChar->GetActorLocation();
						distanceLength = distance.Size();
						///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, checking distance to enemy."), *npc->GetName());
						///UE_LOG(LogTemp, Warning, TEXT("The distance is %f"), distanceLength);

						if (distanceLength < 2500.0 && !otherChar->movementComponent->targeted && otherChar->movementComponent->GetMoveToBattleState() == otherChar->movementComponent->GetMoveToBattleState())
						{
							enemyTarget = otherChar;
							enemyTarget->movementComponent->targeted = true;
							enemyTarget->movementComponent->enemyTarget = npc;
							targeted = true;

							///UE_LOG(LogTemp, Warning, TEXT("The enemy: %s, is within distance of me %s"), *enemyTarget->GetName(), *npc->GetName());

						} 
					} else if (otherChar->isDead)
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s is adding %s to deadChars to be removed"), *npc->GetName(), *otherChar->GetName());

						deadChars.Add(otherChar);
					}
				}

				if (deadChars.Num() > 0)
				{
					for (auto* deadChar : deadChars)
					{
						UE_LOG(LogTemp, Warning, TEXT("%s is the dead npc to be removed, being removed by %s."), *deadChar->GetName(), *npc->GetName());
						otherChars.Remove(deadChar);
					}

					deadChars.Empty();
				}


				//TODO once all enemies are dead, choose the follower with the most kills to become the next leader, then set all others as the new leaders followers.
			} else 
			{
				if (npc->leader && npc->leader->isDead)
				{
					int kills = 0;
					ANPC* newLeader = nullptr;

					UE_LOG(LogTemp, Warning, TEXT("All the enemies of %s are dead."), *npc->GetName());
					//Firstly, we find the follower of this npc with the highest kill count.
					for (auto* follower : npc->leader->followers)
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s is finding the number of followers"), *npc->GetName());
						if (follower->killCount > kills && !follower->isDead)
						{
							kills = follower->killCount;
							newLeader = follower;
						}
					}

					UE_LOG(LogTemp, Warning, TEXT(" %s has the highest kill count of %d."), *newLeader->GetName(), kills);
					npc->replacementLeader = newLeader;

					//npc->npcController->NewLeadersAndFollowers(npc->leader);
					if (npc == npc->replacementLeader)
					{
						curMoveState = EMoveStates::NULLMOVE;
						npc->npcController->SetState(npc->npcController->GetIdleState());
					} else
					{
						//npc->leader = nullptr;
					}
				} else if (!npc->leader || npc->isLeader)
				{
					TArray<ANPC*> deadFollowers;

					for (auto* follower : npc->followers)
					{
						if (follower->isDead)
						{
							deadFollowers.Add(follower);
						}
					}

					if (deadFollowers.Num() > 0)
					{
						for (auto* deadFollower : deadFollowers)
						{
							UE_LOG(LogTemp, Warning, TEXT("Removing follower %s."), *deadFollower->GetName());
							npc->followers.Remove(deadFollower);
						}
						deadFollowers.Empty();
					}

					curMoveState = EMoveStates::NULLMOVE;
					npc->npcController->SetState(npc->npcController->GetIdleState());
				}
		
				hasSeenEnemy = false;
				enemiesAreDead = true;
				///UE_LOG(LogTemp, Warning, TEXT("Setting seenEnemy to false and enemies are all dead true, should also be going to idle state."));
			}

		} else if (enemyTarget)
		{
			if (enemyTarget->movementComponent->enemyTarget == npc)
			{
				curMoveState = EMoveStates::MOVETOENEMY;
			}
		}
	}
	

}

void UNPCMovementComponent::MoveToEnemy(ANPC* npc)
{
	
	if (enemyTarget)
	{
		///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, and is moving to attack %s."), *npc->GetName(), *enemyTarget->GetName());
		
		//Here this npc will check the distance between themselves and their target until a minimum of 4 meters,
		//at which point the canMove bool stops movement and Confrontation causes a transition to attack.

		FVector distance;
		distance = npc->GetActorLocation() - enemyTarget->GetActorLocation();
		targetDistanceLength = distance.Size();


		if (targetDistanceLength < 400.0)
		{
			///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, attacking enemy target."), *npc->GetName());
			moveToEnemyTimer = 120;
			canMove = false;
			confrontation = true;

			npc->npcController->SetState(npc->npcController->GetAttackState());
		}

		if (ensure(npc->npcController))
		{
			///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, moving to enemy target %s and they ."), *npc->GetName(), *enemyTarget->GetName(), (enemyTarget->isLeader ? TEXT("are a leader") : TEXT("are not a leader")));
			MaxWalkSpeed = targetDistanceLength * .35;
			//TODO change moveto to call once
			npc->npcController->MoveToActor(enemyTarget, 150.0);
		}
	} else
	{
		curMoveState = EMoveStates::MOVETOBATTLE;
	}
}

EMoveStates UNPCMovementComponent::GetFollowState()
{
	return EMoveStates::FOLLOW;
}

EMoveStates UNPCMovementComponent::GetMoveToBattleState()
{
	return EMoveStates::MOVETOBATTLE;
}

EMoveStates UNPCMovementComponent::GetMoveToEnemyState()
{
	return EMoveStates::MOVETOENEMY;
}

EMoveStates UNPCMovementComponent::GetMoveToLocationState()
{
	return EMoveStates::MOVETOLOCATION;
}

void UNPCMovementComponent::SetDefaultState(EMoveStates state)
{
	defaultState = state;
}

void UNPCMovementComponent::FilterEnemies(const TArray<AActor*> enemies, ANPC* npc)
{
	if (otherChars.Num() < 5)
	{
		for (auto* enemy : enemies)
		{
			ANPC* actor = Cast<ANPC>(enemy);

			if (actor->GetNPCRace() != npc->GetNPCRace() && !actor->isDead)
			{
				if (!otherChars.Contains(actor))
				{
					otherChars.Add(Cast<ANPC>(actor));
					hasSeenEnemy = true;
					//TODO solve issue with capsule collider colliding with self's OverlapCollider (capsule collider is set not to generate overlap events)
					///UE_LOG(LogTemp, Warning, TEXT("%s was added to %s's array"), *actor->GetName(), *npc->GetName());
				}
			}
		}
	}
}


