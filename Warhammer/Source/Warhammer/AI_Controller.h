// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Movement.h"
#include "GameFramework/Controller.h"
#include "AI_Controller.generated.h"

/**
 * This script will control the AI's states and actions.
 */

UCLASS()
class WARHAMMER_API AAI_Controller : public AMovement
{
	GENERATED_BODY()
	
public:

	// Sets default values for this pawn's properties
	AAI_Controller();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//Function that returns this character
	APawn* GetControlledAI() const;

	//Array used to store all nearby actors
	TArray<AActor*> OverlappingActors;
	
	
};
