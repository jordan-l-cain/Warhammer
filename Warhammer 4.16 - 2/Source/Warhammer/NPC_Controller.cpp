// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPCMovementComponent.h"
#include "Combat.h"
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
		UE_LOG(LogTemp, Warning, TEXT("Movement Component is set, setting state to move"));
		SetState(ENPCStates::MOVE);
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement Component is not set (check this classes BP"));
		return;
	}
}

void ANPC_Controller::StateMove()
{
	npc->movementComponent->MoveAI(npc->npc, npc->OverlappingActors);
	
	if (npc->movementComponent->moveSpeed <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set State to attack"));
		SetState(ENPCStates::ATTACK);
	}
}

void ANPC_Controller::StateAttack()
{
	
	if (npc->npcHealth > 0 && npc->movementComponent->enemyTarget->npcHealth > 0)
	{
		UCombat::Attack(npc, npc->movementComponent->enemyTarget);
	}
	if (npc->npcHealth <= 0)
	{
		SetState(ENPCStates::DIE);
	}
}

void ANPC_Controller::StateDie()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is dead"), *npc->GetName());
}


