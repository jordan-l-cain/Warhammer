// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Movement.generated.h"

class AAI_Controller;

UCLASS()
class WARHAMMER_API AMovement : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovement();

	// Function that handles movement of AI
	void MoveAI( AActor* character, TArray<AActor*> OverlappingActors);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	FVector newLocation;

	//Bool used for one time character ensure and cast
	bool characterCast = false;
	
	//Value for movement speed
	float moveSpeed = 10.0;

	//Used to store distance between two objects
	float distanceLength;

	//Reference pointer to the enemy that is within the minimum distance
	const AActor* enemyTarget = nullptr;
	
	//Array used to store individual overlapping actors so they may be cast
	TArray<AAI_Controller*> otherChars;
};
