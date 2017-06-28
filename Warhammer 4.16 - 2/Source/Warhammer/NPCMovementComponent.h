// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NPCMovementComponent.generated.h"

class ANPC;

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
	float moveSpeed = 10.0;


private:

	FVector newLocation;

	//Used to store distance between two objects
	float distanceLength;

	//Distance used strictly between npc and enemyTarget
	float targetDistanceLength;

	//Array used to store individual overlapping actors so they may be cast
	TArray<ANPC*> otherChars;

	//FVector used for movement direction
	FVector moveDirection;
};
