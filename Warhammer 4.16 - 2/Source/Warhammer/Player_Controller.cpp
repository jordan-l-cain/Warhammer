// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Player_Char.h"
#include "PlayerMovementComponent.h"
#include "Combat.h"
#include "NPC.h"
#include "Player_Controller.h"


void APlayer_Controller::Play()
{

}

void APlayer_Controller::Tick(float DeltaTime)
{
	switch (curState)
	{
	case EPlayerStates::IDLE:
		StateIdle();
		break;

	case EPlayerStates::MOVE:
		StateMove();
		break;

	case EPlayerStates::ATTACK:
		StateAttack();
		break;

	case EPlayerStates::DIE:
		StateDie();
		break;

	default:
		StateIdle();
	}
}

void APlayer_Controller::StateIdle()
{
	UE_LOG(LogTemp, Warning, TEXT("In idle, switching to movement state"));
	SetState(EPlayerStates::MOVE);
}

void APlayer_Controller::StateMove()
{
	if (playerChar)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player name is %s"), *playerChar->GetName());
		playerChar->movementComponent->MovementState();
	}

}

void APlayer_Controller::StateAttack()
{
	if (!playerChar->movementComponent->enemyTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is switching to move state after enemy has died"));
		SetState(EPlayerStates::MOVE);
	}

	if (playerChar->playerHealth <= 0)
	{
		SetState(EPlayerStates::DIE);

	} else if (playerChar->movementComponent->enemyTarget && playerChar->movementComponent->enemyTarget->npcHealth > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s is attacking %s"), *playerChar->GetName(), *playerChar->movementComponent->enemyTarget->GetName());
		//TODO change this so that the attack only runs through once per so that the player can run away
		UCombat::AttackPlayer(playerChar->movementComponent->enemyTarget, playerChar);
	}
}

void APlayer_Controller::StateDie()
{
	//Setup so that if an NPC kills the player they reset like any other combat scenario
}



void APlayer_Controller::SetState(EPlayerStates state)
{
	curState = state;
}

EPlayerStates APlayer_Controller::GetCurState()
{
	return curState;
}

EPlayerStates APlayer_Controller::GetIdleState()
{
	return EPlayerStates::IDLE;
}

EPlayerStates APlayer_Controller::GetMoveState()
{
	return EPlayerStates::MOVE;
}

EPlayerStates APlayer_Controller::GetAttackState()
{
	return EPlayerStates::ATTACK;
}

EPlayerStates APlayer_Controller::GetDieState()
{
	return EPlayerStates::DIE;
}

