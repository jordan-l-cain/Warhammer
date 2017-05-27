// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Movement.h"


// Sets default values
AMovement::AMovement()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AMovement::BeginPlay()
{
	Super::BeginPlay();

	//AddMovementInput();
}

// Called every frame
void AMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMovement::MoveAI( APawn* character, TArray<AActor*> OverlappingActors)
{
	///overlapping actors array passed by the ai
	GetOverlappingActors(OverlappingActors);

	AddMovementInput(GetActorForwardVector(), moveSpeed);

	//TODO check the tag passed by the characters in overlappingactors
	FName enemyTag = FName(TEXT("enemy"));

	for (const auto* actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is overlapped with %s."), *actor->GetName(), *character->GetName());
		
		///Using movespeed of this ai as a parameter for when to stop checking distances of others
		if (actor->ActorHasTag(enemyTag) && moveSpeed > 0.0) 
		{
			///UE_LOG(LogTemp, Warning, TEXT("enemy has tag"));
			FVector distance;

			///Find distance between this ai and 
			distance = character->GetActorLocation() - actor->GetActorLocation();
			distanceLength = distance.Size();

			UE_LOG(LogTemp, Warning, TEXT("The distance is %f"), distanceLength);

		}else
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
//TODO create playercontroller and aicontroller classes, they will pass their overlapping actor array as well as their target. The array will be used in this script to ensure they maneuver around each other and obstacles