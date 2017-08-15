// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Player_Char.h"
#include "PlayerMovementComponent.h"
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

}

void APlayer_Controller::StateDie()
{

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

