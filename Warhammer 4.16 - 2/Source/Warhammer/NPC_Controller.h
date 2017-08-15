// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_Controller.generated.h"

class ANPC;
class UNPCMovementComponent;
class AWarhammerGameModeBase;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ENPCStates : uint8
{
	IDLE UMETA(DisplayName = "Idle"),
	MOVE UMETA(DisplayName = "Move"),
	ATTACK UMETA(DisplayName = "Attack"),
	ATTACKPLAYER UMETA(DisplayName = "AttackPlayer"),
	DIE UMETA(DisplayName = "Die")
};

/**
 * This class will handle all run-time NPC States and calling of Actions, delegated out to their respective classes
 */
UCLASS(Blueprintable)
class WARHAMMER_API ANPC_Controller : public AAIController
{
	GENERATED_BODY()
	
public:

	// Sets default values for this pawn's properties
	ANPC_Controller();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//ANPC class instance
	ANPC* npc;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//GameMode instance used to access global variables such as dead dwarf and greenskin count
	AWarhammerGameModeBase* GameMode;

	//Function that sets the AI's state
	void SetState(ENPCStates state);

	//Function that returns the current state
	ENPCStates GetCurState();

	//Function that returns the idle state
	ENPCStates GetIdleState();

	//Function that returns the Move state
	ENPCStates GetMoveState();

	//Function that returns the Attack state
	ENPCStates GetAttackState();

	//Function that returns the Attack state
	ENPCStates GetAttackPlayerState();

	//Function that returns the Die state
	ENPCStates GetDieState();

	//Function that sets a new leader and their followers after combat. Called from NPCMovement when all enemies are dead in otherChars.
	void NewLeadersAndFollowers(ANPC* leader, ANPC* newLeader);

	UPROPERTY(VisibleAnywhere, Category = "NPC Settings")
	//Current state the AI is in
	ENPCStates curState;


protected:
	
	UFUNCTION(BlueprintCallable, Category= "Functions")
	void Play();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	// Called every frame
	void Tick(float DeltaTime);



private:

	void StateIdle();

	void StateMove();

	void StateAttack();

	void StateAttackPlayer();

	void StateDie();

};

