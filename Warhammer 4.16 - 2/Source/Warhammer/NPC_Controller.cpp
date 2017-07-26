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
	if (ensure(npc))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the npc"), *npc->GetName());
		SetState(ENPCStates::IDLE);

	} else
	{
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

void ANPC_Controller::StateIdle()
{
	UE_LOG(LogTemp, Warning, TEXT("AI is idling"));
	if (ensure(npc->movementComponent))
	{
		///UE_LOG(LogTemp, Warning, TEXT("Movement Component is set, setting state to move"));
		SetState(ENPCStates::MOVE);
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement Component is not set (check this classes BP)"));
		return;
	}
}

void ANPC_Controller::StateMove()
{
	if (npc->npcType == npc->GetCommonType())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Common Type called"))
		npc->movementComponent->SetDefaultState(npc->movementComponent->GetFollowState());
		npc->movementComponent->MoveAI(npc->npc, npc->OverlappingActors);
	}

	if (npc->npcType == npc->GetChampionType())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Champion Type called"))
		npc->movementComponent->SetDefaultState(npc->movementComponent->GetMoveToEnemyState());
		npc->movementComponent->MoveAI(npc->npc, npc->OverlappingActors);
	}
	
	if (npc->movementComponent->confrontation)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Set State to attack"));
		SetState(ENPCStates::ATTACK);
	}
}

void ANPC_Controller::StateAttack()
{
	if (!npc->movementComponent->enemyTarget)
	{
		npc->movementComponent->canMove = true;
		npc->movementComponent->confrontation = false;
		npc->movementComponent->targeted = false;
		SetState(ENPCStates::IDLE);
	}

	if (npc->npcHealth <= 0)
	{
		SetState(ENPCStates::DIE);

	}else if (npc->movementComponent->confrontation && npc->npcHealth > 0 && ensure(npc->movementComponent->enemyTarget) && npc->movementComponent->enemyTarget->npcHealth > 0)
	{
		UCombat::Attack(npc, npc->movementComponent->enemyTarget);
	}
}

void ANPC_Controller::StateDie()
{
	//Changes this npc's death bool to true so that anyone colliding with/any arrays it's in will read it's dead, then ignore or remove it.
	//Also sets the enemyTarget of the npc that targeted this one to null, so that npc will reset to Idle.

	if (npc->dwarf)
	{
		GameMode->deadDwarfs += 1;
		AWarhammerGameModeBase::PrintKills(GameMode->deadDwarfs, GameMode->deadGreenskins);
	}
	if (npc->greenskin)
	{
		GameMode->deadGreenskins += 1;
		AWarhammerGameModeBase::PrintKills(GameMode->deadDwarfs, GameMode->deadGreenskins);
	}

	npc->isDead = true;
	npc->movementComponent->enemyTarget->movementComponent->enemyTarget = nullptr;
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	/*
	if (npc->movementComponent->otherChars.Contains(npc))
	{
		npc->movementComponent->otherChars.Remove(npc);
	}*/
	
}

//TODO test combat with multiple npcs to fine tune stats, get static ints working
//TODO get npc to continue after killing a target

