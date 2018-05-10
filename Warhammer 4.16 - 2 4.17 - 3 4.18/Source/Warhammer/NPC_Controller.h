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
	DIALOGUE UMETA(DisplayName = "Dialogue"),
	EVENT UMETA(DisplayName = "Event"),
	INTOWN UMETA(DisplayName = "InTown"),
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

	//Function that returns the AttackPlayer state
	ENPCStates GetAttackPlayerState();

	//Function that returns the Dialogue state
	ENPCStates GetDialogueState();

	//Function that returns the Event state
	ENPCStates GetEventState();

	//Function that returns the InTown state
	ENPCStates GetInTownState();

	//Function that returns the Die state
	ENPCStates GetDieState();

	//Function that sets a new leader and their followers after combat. Called from NPCMovement when all enemies are dead in otherChars.
	void NewLeadersAndFollowers(ANPC* leader, ANPC* newLeader);

	UPROPERTY(VisibleAnywhere, Category = "NPC Settings")
	//Current state the AI is in
	ENPCStates curState;

	//Function that will switch the state to a dialogue state so that a dialogue may occur
	UFUNCTION(BlueprintCallable, Category="Functions")
	void EnterDialogueState();

	//Function that will send the npc into an event, and move them to a given location
	void EnterEvent(AActor* eventLocation, TArray<AActor*> positions);

	//Blueprint event that will check the boolean of the given position object and return true or false
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void PositionVacant(AActor* position);

	//Blueprint event that will change boolean of a given position to true, simulating occupation
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OccupyPosition(AActor* position);

	//TArray of event positions passed from WorldEvents, found in WarhammerGameModeBase
	TArray<AActor*> eventPositions;

	UPROPERTY(BlueprintReadWrite, Category = "Events")
	//Boolean controlled by the PositionVacant event, representing the vacancy boolean of an event position
	bool vacant = true;

	//Boolean used by world events in case the npc is in combat, will be set to true in the enter event function, but checked only in state idle
	bool enterEvent = false;

	//EventLocation variable for npc's who enter the event late
	AActor* currentEventLocation;

	//Boolean used to ensure the leader only sends their followers to an event once
	bool followersEnterEvent = true;

	//Boolean used to determine when the npc is at their event position
	bool atEventPosition = false;

	//Index for setting follower's targets for combat
	int combatIndex;

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//Event used to lock the npc onto the player, via blueprint
	void PlayerLockOn(AActor* player);

	UFUNCTION(BlueprintImplementableEvent)
	//Used to delay the AddNPC function in locations.h to help performance
	void DelayAdd(ANPC* locationNPC);

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

	void StateDialogue();

	void StateEvent();

	void StateInTown();

	void StateDie();

	//Used in the event state to check positions and send followers to them
	int positionIndex = 0;

};

