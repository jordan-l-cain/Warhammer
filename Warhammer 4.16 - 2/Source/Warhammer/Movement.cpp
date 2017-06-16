// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "AI_Controller.h"
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

void AMovement::MoveAI(AAI_Controller* character, TArray<AActor*> OverlappingActors)
{
	if (!enemyTarget)
	{
		if (ensure(character))
		{
			moveDirection = character->GetActorForwardVector();

		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("character pointer is null."));
			return;
		}


		for (auto* actor : OverlappingActors)
		{
			if (!otherChars.Contains(actor))
			{
				otherChars.Add(Cast<AAI_Controller>(actor));
				UE_LOG(LogTemp, Warning, TEXT("an actor was added to the array"));
			}

		}

		for (auto* otherChar : otherChars)
		{
			if (!ensure(otherChar))
			{
				UE_LOG(LogTemp, Warning, TEXT("otherChar pointer is null."));
				return;

				//UE_LOG(LogTemp, Warning, TEXT("%s is overlapped with %s."), *otherChar->GetName(), *character->GetName());
				//UE_LOG(LogTemp, Warning, TEXT("This character's type is %s."), *thisChar->GetCharacterType());
			}

			///Using movespeed of this ai as a parameter for when to stop checking distances of others
			///if ((thisChar->GetCharacterType() != otherChar->GetCharacterType()) && moveSpeed > 0.0) 
			if (character->GetCharacterType() != otherChar->GetCharacterType() && moveSpeed > 0.0)
			{
				///Find distance between this ai and each enemy in the overlapping actors array
				FVector distance;
				distance = character->GetActorLocation() - otherChar->GetActorLocation();
				distanceLength = distance.Size();

				///UE_LOG(LogTemp, Warning, TEXT("The distance is %f"), distanceLength);

				if (distanceLength < 2000.0 && !targeted && !otherChar->targeted)
				{
					enemyTarget = otherChar;
					enemyTarget->targeted = true;
					enemyTarget->enemyTarget = character;
					targeted = true;

					UE_LOG(LogTemp, Warning, TEXT("The enemy: %s, is within distance"), *enemyTarget->GetName());

				} else if (otherChar->targeted && moveSpeed > 0.0)
				{
					UE_LOG(LogTemp, Warning, TEXT("%s is already targeted"), *otherChar->GetName());
				}

				if (targeted)
				{
					moveSpeed = 0.0;
				}

			} else if (character->GetCharacterType() == otherChar->GetCharacterType())
			{
				UE_LOG(LogTemp, Warning, TEXT("%s is the same class as me: %s"), *otherChar->GetName(), *character->GetName());

			}
		}

		AddMovementInput(moveDirection, moveSpeed);
	}

	//TODO make characters targeting each other move towards each other
	if (enemyTarget)
	{
		moveSpeed = 0.1;

		///Find distance between this ai and each enemy in the overlapping actors array
		FVector distance;
		distance = character->GetActorLocation() - enemyTarget->GetActorLocation();
		targetDistanceLength = distance.Size();

		if (targetDistanceLength < 800.0)
		{
			moveSpeed = 0.0;
		}

		AddMovementInput(moveDirection, moveSpeed);
	}
	
	
}
//TODO create playercontroller and aicontroller classes, they will pass their overlapping actor array as well as their target. The array will be used in this script to ensure they maneuver around each other and obstacles