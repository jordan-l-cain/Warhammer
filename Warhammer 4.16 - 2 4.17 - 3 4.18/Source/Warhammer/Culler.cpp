// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Culler.h"


// Sets default values
ACuller::ACuller()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACuller::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACuller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

