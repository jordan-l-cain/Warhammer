// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Player_Char.h"


// Sets default values
APlayer_Char::APlayer_Char()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayer_Char::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_Char::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayer_Char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

