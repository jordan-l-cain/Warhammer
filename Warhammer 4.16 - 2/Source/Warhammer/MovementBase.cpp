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

	MoveCharacter();
}

//TODO Create parameters for an FVector that controls direction( for AI forward or rotate towards enemy) as well as speed
void AMovementBase::MoveCharacter()
{	
	AddMovementInput(GetActorForwardVector(), movSpeed);

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	FName enemyTag = FName(TEXT("enemy"));

	for (const auto* actor : OverlappingActors)
	{

		if (actor->ActorHasTag(enemyTag) && movSpeed > 0.0)
		{
			///UE_LOG(LogTemp, Warning, TEXT("enemy has tag"));
			FVector distance;
			distance = GetActorLocation() - actor->GetActorLocation();
			distanceLength = distance.Size();
			UE_LOG(LogTemp, Warning, TEXT("The distance is %f"), distanceLength);
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("actor is not tagged"));
		}


		if (distanceLength < 1600.0)
		{
			movSpeed = 0.0;
			
			enemyTarget = actor;

			UE_LOG(LogTemp, Warning, TEXT("The enemy: %s, is within distance"), *enemyTarget->GetName());
		}
	
	}


	
}
/*

*/