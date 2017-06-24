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

// Called when the game starts or when spawned
void AAI_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the character"), *character->GetName())
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

ECharacterType AAI_Controller::GetCharacterType()
{
	return characterType;
}

void AAI_Controller::ModHealth(float modifier)
{
	if (characterHealth > 0)
	{
		characterHealth += modifier;
		UE_LOG(LogTemp, Warning, TEXT("%s's health is %f"), *character->GetName(), characterHealth);

	}
	if (characterHealth <= 0)
	{
		characterHealth = 0;
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
	MoveAI(character, OverlappingActors);

	if (moveSpeed <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set State to attack"));
		SetState(AIStates::ATTACK);
	}
}

void AAI_Controller::StateAttack()
{
	if (characterHealth > 0 && enemyTarget->characterHealth > 0)
	{
		UCombat::Attack(character, enemyTarget);
	}
}

void AAI_Controller::StateDie()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is dead"), *character->GetName());
	return;
}