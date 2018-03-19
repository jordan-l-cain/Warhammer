// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player_Controller.generated.h"


enum class EPlayerStates : uint8
{
	IDLE UMETA(DisplayName = "Idle"),
	MOVE UMETA(DisplayName = "Move"),
	ATTACK UMETA(DisplayName = "Attack"),
	DIE UMETA(DisplayName = "Die")
};

class APlayer_Char;

/**
 * 
 */
UCLASS()
class WARHAMMER_API APlayer_Controller : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable, Category = "Functions")
	void Play();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	// Called every frame
	void Tick(float DeltaTime);

public:

	UPROPERTY(BlueprintReadWrite, Category = "Player Settings")
	//Pointer to the player
	APlayer_Char* playerChar;

	//Function that sets the AI's state
	void SetState(EPlayerStates state);

	//Function that returns the current state
	EPlayerStates GetCurState();

	//Function that returns the idle state
	EPlayerStates GetIdleState();

	//Function that returns the Move state
	EPlayerStates GetMoveState();

	//Function that returns the Attack state
	EPlayerStates GetAttackState();

	//Function that returns the Die state
	EPlayerStates GetDieState();

	//Moves the player to a given location
	void MoveToLocation(FVector destination);

private:

	//Current state of the player
	EPlayerStates curState;

	void StateIdle();

	void StateMove();

	void StateAttack();

	void StateDie();
	
};
