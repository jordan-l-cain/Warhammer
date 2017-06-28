// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Combat.h"
#include "AI_Controller.h"

// Sets default values
AAI_Controller::AAI_Controller()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//AIStatesDictionary.Add(AIStates::IDLE, StateIdle());

}
/*
// Called when the game starts or when spawned
void AAI_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the npc"), *npc->GetName())
	}
	
	SetState(AIStates::IDLE);
}

// Called every frame
void AAI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (curState)
	{
		case AIStates::IDLE :
			StateIdle();
		break;

		case AIStates::MOVE :
			StateMove();
		break;

		case AIStates::ATTACK:
			StateAttack();
		break;

		case AIStates::DIE:
			StateDie();
		break;

		default:
			StateIdle();
	}
}

// Called to bind functionality to input
void AAI_Controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

ENPCType AAI_Controller::GetNPCType()
{
	return npcType;
}

void AAI_Controller::ModHealth(float modifier)
{
	if (npcHealth > 0)
	{
		npcHealth += modifier;
		UE_LOG(LogTemp, Warning, TEXT("%s's health is %f"), *npc->GetName(), npcHealth);

	}
	if (npcHealth <= 0)
	{
		npcHealth = 0;
		SetState(AIStates::DIE);
	}
}

void AAI_Controller::ModCanAttack(bool boolean)
{
	canAttack = boolean;
}

bool AAI_Controller::GetCanAttack()
{
	return canAttack;
}

void AAI_Controller::SetState(AIStates state)
{
	curState = state;
}

void AAI_Controller::StateIdle()
{
	UE_LOG(LogTemp, Warning, TEXT("AI is idling"));
	SetState(AIStates::MOVE);
}

void AAI_Controller::StateMove()
{
	MoveAI(npc, OverlappingActors);

	if (moveSpeed <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set State to attack"));
		SetState(AIStates::ATTACK);
	}
}

void AAI_Controller::StateAttack()
{
	if (npcHealth > 0 && enemyTarget->npcHealth > 0)
	{
		UCombat::Attack(npc, enemyTarget);
	}
}

void AAI_Controller::StateDie()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is dead"), *npc->GetName());
}
*/