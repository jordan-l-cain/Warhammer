// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NPCMovementComponent.generated.h"

class ANPC;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EMoveStates : uint8
{
	NULLMOVE UMETA(DisplayName = "Null"),
	MOVETOLOCATION UMETA(DisplayName = "MoveToLocation"),
	FOLLOW UMETA(DisplayName = "Follow"),
	MOVETOBATTLE UMETA(DisplayName = "MoveToBattle"),
	MOVETOENEMY UMETA(DisplayName = "MoveToEnemy"),
	MOVETOPLAYER UMETA(DisplayName = "MoveToPlayer")
};

/**
 * This class controls all NPC Movement
 */
UCLASS()
class WARHAMMER_API UNPCMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
	virtual void InitializeComponent() override;
	
	

protected:


public:

	// Function that handles movement of AI
	void MoveAI(ANPC* npc);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Boolean that's used to determine when two npcs have targeted eachother for attack
	bool targeted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Pointer to the enemy that is within the minimum distance
	ANPC* enemyTarget = nullptr;

	//Pointer to the player. Set by player, who calls event when player checks minimum distance to npcs
	AActor* playerTarget = nullptr;

	//Enemy Leader target variable. Set when an enemy leader is within distance, which will create a middle point between leaders and they will move to the mutual location.
	ANPC* enemyLeader = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Value for movement speed
	bool canMove = true;

	float originalSpeed;

	//Used to limit the followers move to calls
	float timer = 50;

	//Index of this follower in their leader's array, used to determine location in formation
	int followerIndex;

	//Location between two enemy leaders, set when they are within distance.
	FVector middlePoint;

	//Bool used in the move to location function so that leaders only call the moveto(middlepoint) once.
	bool moveToLeader;

	//timer used in the MoveToLocation function
	int locationTimer = 0;

	//timer used in MoveToEnemy function to regulate amount of moveTo calls
	int moveToEnemyTimer = 120;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//This bool will be checked at beginning of movetoEnemy to prevent early termination of combat.
	bool hasSeenEnemy = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//This bool will prevent running any commands out of the moveToEnemy state.
	bool enemiesAreDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Used so that the leaders will set their followers state to move to enemy only once per combat.
	bool setFollowersMoveToEnemy = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Array of casted overlapping actors, filtered by the FlterEnemies function so it only contains enemies.
	TArray<ANPC*> otherChars;

	//Bool used to determine when two npc's can fight
	bool confrontation;

	UPROPERTY(VisibleAnywhere, Category = "NPC Settings")
	//Enum variable defining the current movement state
	EMoveStates curMoveState = EMoveStates::NULLMOVE;

	//Return function that will return the Follow state
	EMoveStates GetFollowState();

	//Return function that will return the Move To Enemy state
	EMoveStates GetMoveToBattleState();

	//Return function that will return the Move To Enemy state
	EMoveStates GetMoveToEnemyState();

	//Return function that will return the Move To Location state
	EMoveStates GetMoveToLocationState();

	//Function that sets the default state of the switch for the movement states
	void SetDefaultState(EMoveStates defaultState);

	//Function used to find all designated leaders at the start of the game.
	UFUNCTION(BlueprintCallable, Category = "Functions")
	void FilterEnemies (const TArray<AActor*> enemies, ANPC* npc);

	//Function that will set the player as the npc's target
	void PlayerAttack(AActor* player);

private:

	FVector newLocation;

	//Used to store distance between two objects
	float distanceLength;

	//Distance used strictly between npc and enemyTarget
	float targetDistanceLength;

	//FVector used for movement direction
	FVector moveDirection;
	
	//Used to reset the npc's rotation
	FRotator originalRotation;

	//Enum Variable used for the default state
	EMoveStates defaultState;

	//Follow function, which will make AI follow a target
	void Follow(ANPC* npc);

	//Move To Battle Function, is used to bring npcs within distance of each other and select a target
	void MoveToBattle(ANPC* npc);

	//Move To Enemy function, once two npcs target each other, this state is called move them to each other and attack
	void MoveToEnemy(ANPC* npc);

	//Move To Player function, which is a clone of MoveToEnemy
	void MoveToPlayer(ANPC* npc);

	//Move To Location function, which is where leaders will decide where to move to, be it a location or towards an enemy
	void MoveToLocation(ANPC* npc);
};
