// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NPCMovementComponent.generated.h"

class ANPC;

enum class EMoveStates : uint8
{
	NULLMOVE UMETA(DisplayName = "Null"),
	FOLLOW UMETA(DisplayName = "Follow"),
	MOVETOENEMY UMETA(DisplayName = "MoveToEnemy"),
	MOVETOLOCATION UMETA(DisplayName = "MoveToLocation")
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
	void MoveAI(ANPC* npc, TArray<AActor*> OverlappingActors);

	//Boolean that's used to determine when two npcs have targeted eachother for attack
	bool targeted = false;

	//Reference pointer to the enemy that is within the minimum distance
	ANPC* enemyTarget = nullptr;

	//Value for movement speed
	bool canMove = true;

	float originalSpeed;

	//Used to limit the followers move to calls
	float timer = 50;

	//Index of this follower in their leader's array, used to determine location in formation
	int followerIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Array used to store individual overlapping actors so they may be cast
	TArray<ANPC*> otherChars;

	//Bool used to determine when two npc's can fight
	bool confrontation;

	//Enum variable defining the current movement state
	EMoveStates curMoveState = EMoveStates::NULLMOVE;

	//Return function that will return the Follow state
	EMoveStates GetFollowState();

	//Return function that will return the Move To Enemy state
	EMoveStates GetMoveToEnemyState();

	//Return function that will return the Move To Location state
	EMoveStates GetMoveToLocationState();

	//Function that sets the default state of the switch for the movement states
	void SetDefaultState(EMoveStates defaultState);

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

	//Move To Enemy function
	void MoveToEnemy(ANPC* npc, TArray<AActor*> OverlappingActors);

	//Move To Location function, which is where leaders will decide where to move to, be it a location or towards an enemy
	void MoveToLocation();
};
