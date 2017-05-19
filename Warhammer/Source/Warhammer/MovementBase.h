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

	//TODO Set up parameters to affect speed, direction and possibly distance
	//Movement function for AI
	virtual void MoveCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//Pawn of instance of script
	AActor* thisPawn; 

	
};
