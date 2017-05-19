// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "MovementBase.h"


// Sets default values
AMovementBase::AMovementBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovementBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//TODO Create generic movement
void AMovementBase::MoveCharacter()
{
	//TODO Self Reference movement at a reasonable speed
	
	///Find Self with Get Pawn, assign to variable (possibly public through function?)
	///Move pawn forward
}