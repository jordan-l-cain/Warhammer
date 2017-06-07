// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MovementBase.generated.h"

UCLASS()
class WARHAMMER_API AMovementBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMovementBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Movement function for AI
	virtual void MoveCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	FVector newLocation;

	//Value for movement speed
	float movSpeed = 10.0;

	//Used to store distance between two objects
	float distanceLength;

	//Reference pointer to the enemy that is within the minimum distance
	const AActor* enemyTarget = nullptr ;
	
};
