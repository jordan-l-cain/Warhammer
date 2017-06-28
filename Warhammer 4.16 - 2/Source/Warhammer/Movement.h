// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Movement.generated.h"

class ANPC_Controller;

UCLASS(Blueprintable)
class WARHAMMER_API AMovement : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovement();

	// Function that handles movement of AI
	void MoveAI(ANPC_Controller* npc, TArray<AActor*> OverlappingActors);

	//Boolean that's used to determine when two npcs have targeted eachother for attack
	bool targeted = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Reference pointer to the enemy that is within the minimum distance
	ANPC_Controller* enemyTarget = nullptr;

	//Value for movement speed
	float moveSpeed = 10.0;

private:

	FVector newLocation;

	//Used to store distance between two objects
	float distanceLength;

	//Distance used strictly between npc and enemyTarget
	float targetDistanceLength;
	
	//Array used to store individual overlapping actors so they may be cast
	TArray<ANPC_Controller*> otherChars;

	//FVector used for movement direction
	FVector moveDirection;

};
