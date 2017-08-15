// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPCMovementComponent.h"
#include "Combat.h"
#include "WarhammerGameModeBase.h"
#include "NPC_Controller.h"

// Sets default values
ANPC_Controller::ANPC_Controller()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC_Controller::Play()
{
	if (ensure(npc) && ensure(npc->movementComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the npc"), *npc->GetName());
		SetState(ENPCStates::IDLE);

	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("A Reference is not set."));
		return;
	}
	
}

// Called every frame
void ANPC_Controller::Tick(float DeltaTime)
{
	switch (curState)
	{
		case ENPCStates::IDLE:
			StateIdle();
			break;

		case ENPCStates::MOVE:
			StateMove();
			break;

		case ENPCStates::ATTACK:
			StateAttack();
			break;

		case ENPCStates::ATTACKPLAYER:
			StateAttackPlayer();
			break;

		case ENPCStates::DIE:
			StateDie();
			break;

		default:
			StateIdle();
	}
}


void ANPC_Controller::SetState(ENPCStates state)
{
	curState = state;
}

ENPCStates ANPC_Controller::GetCurState()
{
	return curState;
}

ENPCStates ANPC_Controller::GetIdleState()
{
	return ENPCStates::IDLE;
}

ENPCStates ANPC_Controller::GetMoveState()
{
	return ENPCStates::MOVE;
}

ENPCStates ANPC_Controller::GetAttackState()
{
	return ENPCStates::ATTACK;
}

ENPCStates ANPC_Controller::GetAttackPlayerState()
{
	return ENPCStates::ATTACKPLAYER;
}

ENPCStates ANPC_Controller::GetDieState()
{
	return ENPCStates::DIE;
}

void ANPC_Controller::NewLeadersAndFollowers(ANPC* leader, ANPC* newLeader)
{
	
	UE_LOG(LogTemp, Warning, TEXT("%s is the new leader"), *npc->GetName());
	UE_LOG(LogTemp, Warning, TEXT("%s is the old leader"), *leader->GetName());

	
	//Here we iterate through the old leader's followers. If the follower is not the new leader npc, then we set the leader of the follwer to the new leader
	//and we add that follower to the new leader's followers
	for (auto* oldFollower : leader->followers)
	{
		if (!newLeader->followers.Contains(oldFollower) && oldFollower != newLeader && !oldFollower->isDead)
		{
			oldFollower->leader = newLeader;
			newLeader->followers.Add(oldFollower);
		}
	}
	
	newLeader->waypoint = leader->waypoint;
	
	if (leader->leader)
	{
		newLeader->leader = leader->leader;
	} else
	{
		newLeader->leader = nullptr;
	}


	UE_LOG(LogTemp, Warning, TEXT("The new leader added itself to it's followers as well as added the followers"));
	
	//Here set the newLeader's leader variable to whatever the old leader's leader was, and change the isLeader boolean to true, as well as type to Champion

	//TODO Base on whether a champion goes to a follow state on whether their leader variable is empty? Change in the StateMove function

	newLeader->isLeader = true;
	newLeader->npcType = newLeader->GetChampionType();

	
	UE_LOG(LogTemp, Warning, TEXT("Calling the replace leader function"));
	AWarhammerGameModeBase::ReplaceLeader(AWarhammerGameModeBase::LeaderList.Find(leader), newLeader, leader);
	
}


void ANPC_Controller::StateIdle()
{
	///UE_LOG(LogTemp, Warning, TEXT("%s is idling, Is leader true?: %s"), *npc->GetName(), (npc->isLeader ? TEXT("True") : TEXT("False")));

	npc->movementComponent->enemiesAreDead = false;

	//TODO Leader AI not moving after enemies are all gone
	if (npc == npc->replacementLeader)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the replacement leader, calling the new leaders function"), *npc->GetName());
		NewLeadersAndFollowers(npc->leader, npc);
		npc->replacementLeader = nullptr;
	}

	if (ensure(npc->movementComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement Component is set, setting state to move"));

		if (npc->isLeader)
		{
			for (auto* follower : npc->followers)
			{
				
				follower->npcController->SetState(follower->npcController->GetIdleState());
				follower->movementComponent->curMoveState = follower->movementComponent->GetFollowState();
			}
		}
		
		SetState(ENPCStates::MOVE);

	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement Component is not set (check this classes BP)"));
		return;
	}
}

void ANPC_Controller::StateMove()
{
	npc->CallMoveStateEvent();
	//TODO Make movement state have nothing to do with the leader, so leaders and followers can be set quicker
	if (npc->npcType == npc->GetCommonType())
	{
		///UE_LOG(LogTemp, Warning, TEXT("Common Type called"));
		npc->movementComponent->SetDefaultState(npc->movementComponent->GetFollowState());
	}

	if (npc->npcType == npc->GetChampionType() && npc->isLeader && !npc->leader)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Champion Type called"));

		npc->movementComponent->SetDefaultState(npc->movementComponent->GetMoveToLocationState());
	
	} else if(npc->npcType == npc->GetChampionType() && npc->isLeader && npc->leader)
	{
		UE_LOG(LogTemp, Warning, TEXT("Champion/Leader %s has a leader"), *npc->GetName());
		npc->movementComponent->SetDefaultState(npc->movementComponent->GetFollowState());
	}

	npc->movementComponent->MoveAI(npc);
}

void ANPC_Controller::StateAttack()
{
	//Here the npc should be moving to enemy until they can attack. Right now this is only called when the npc actually attacks

	//Here we run through the combat function until either this npc dies, or their opponent dies. If their opponent dies, then they set this npc's enemyTarget to null, so that this npc can resume
	if (!npc->movementComponent->enemyTarget)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Enemy target null of %s, going to state IDLE."), *npc->GetName());
		npc->killCount++;
		npc->movementComponent->canMove = true;
		npc->movementComponent->confrontation = false;
		npc->movementComponent->targeted = false;
		SetState(ENPCStates::MOVE);
	}
	


	if (npc->npcHealth <= 0)
	{
		SetState(ENPCStates::DIE);

	}else if (npc->movementComponent->confrontation && npc->npcHealth > 0 && ensure(npc->movementComponent->enemyTarget) && npc->movementComponent->enemyTarget->npcHealth > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s is attacking %s"), *npc->GetName(), *npc->movementComponent->enemyTarget->GetName());
		//TODO change this so that the attack only runs through once per
		UCombat::Attack(npc, npc->movementComponent->enemyTarget);
	}
}

void ANPC_Controller::StateAttackPlayer()
{

	if (npc->npcHealth <= 0)
	{
		SetState(ENPCStates::DIE);

	} else if (npc->movementComponent->confrontation && npc->npcHealth > 0 && ensure(npc->movementComponent->enemyTarget) && npc->movementComponent->enemyTarget->npcHealth > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s is attacking %s"), *npc->GetName(), *npc->movementComponent->enemyTarget->GetName());
		//TODO change this so that the attack only runs through once per
		UCombat::Attack(npc, npc->movementComponent->enemyTarget);
	}

}

void ANPC_Controller::StateDie()
{
	//Changes this npc's death bool to true so that anyone colliding with/any arrays it's in will read it's dead, then ignore or remove it.
	//TODO change this procedure into an actual method callable from any script with an array, where it asks for an item to remove as a parameter, then removes it, that way it is only called once from any npc that dies.
	//Also sets the enemyTarget of the npc that targeted this one to null, so that npc will reset to Idle.

	///UE_LOG(LogTemp, Warning, TEXT("%s has died"), *npc->GetName());
	if (npc->dwarf)
	{
		GameMode->deadDwarfs += 1;
		UE_LOG(LogTemp, Warning, TEXT("The number of dead dwarfs is: %d, and the number of dead greenskins is: %d."), GameMode->deadDwarfs, GameMode->deadGreenskins);
	}
	if (npc->greenskin)
	{
		GameMode->deadGreenskins += 1;
		UE_LOG(LogTemp, Warning, TEXT("The number of dead dwarfs is: %d, and the number of dead greenskins is: %d."), GameMode->deadDwarfs, GameMode->deadGreenskins);
	}
	
	npc->isDead = true;
	npc->isLeader = false;
	npc->movementComponent->enemyTarget->movementComponent->enemyTarget = nullptr;
	npc->SetActorEnableCollision(false);
	//npc->GetRootComponent()->SetWorldRotation(FRotator(0, 90, 0));
	//FVector newLocation = (npc->GetActorLocation(), npc->GetActorLocation(), npc->GetActorLocation() - 80);

	//npc->SetActorLocation(newLocation);

	SetActorTickEnabled(false);
}


//TODO test combat with multiple npcs to fine tune stats
//TODO get npc to continue after killing a target

