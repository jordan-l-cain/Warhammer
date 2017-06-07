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

void AMovement::MoveAI( AActor* character, TArray<AActor*> OverlappingActors)
{
	if (!characterCast)
	{
		if (ensure(character))
		{
			UE_LOG(LogTemp, Warning, TEXT("character name: %s is attempting to cast from %s to AAI_Controller"), *character->GetName(), *character->GetActorClass()->GetFName().ToString());

			AAI_Controller* thisChar = Cast<AAI_Controller>(character->GetOwner());

			if (!ensure(thisChar))
			{
				UE_LOG(LogTemp, Warning, TEXT("thisChar pointer (character cast) is null."));
				return;
			}

		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("character pointer is null."));
			return;
		}

		characterCast = true;
	}

	if (ensure(character))
	{
		AddMovementInput(character->GetActorForwardVector(), moveSpeed);

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

		//TODO Comparison of enums should work, but thisChar cast from character is creating a null pointer
		///Using movespeed of this ai as a parameter for when to stop checking distances of others
		///if ((thisChar->GetCharacterType() != otherChar->GetCharacterType()) && moveSpeed > 0.0) 
		if ( moveSpeed > 0.0)
		{
			
			///UE_LOG(LogTemp, Warning, TEXT("enemy has tag"));
			FVector distance;

			///Find distance between this ai and 
			distance = character->GetActorLocation() - otherChar->GetActorLocation();
			distanceLength = distance.Size();

			UE_LOG(LogTemp, Warning, TEXT("The distance is %f"), distanceLength);

		}else
		{
			//UE_LOG(LogTemp, Warning, TEXT("actor is not tagged"));
		}


		if (distanceLength < 1600.0)
		{
			moveSpeed = 0.0;

			enemyTarget = otherChar;

			UE_LOG(LogTemp, Warning, TEXT("The enemy: %s, is within distance"), *enemyTarget->GetName());
		}
	}
	
}
//TODO create playercontroller and aicontroller classes, they will pass their overlapping actor array as well as their target. The array will be used in this script to ensure they maneuver around each other and obstacles