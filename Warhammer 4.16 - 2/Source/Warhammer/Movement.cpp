// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC_Controller.h"
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

void AMovement::MoveAI(ANPC_Controller* npc, TArray<AActor*> OverlappingActors)
{
	if (!enemyTarget)
	{
		if (ensure(npc))
		{
			moveDirection = npc->GetActorForwardVector();

		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("npc pointer is null."));
			return;
		}


		for (auto* actor : OverlappingActors)
		{
			if (!otherChars.Contains(actor))
			{
				otherChars.Add(Cast<ANPC_Controller>(actor));
				UE_LOG(LogTemp, Warning, TEXT("an actor was added to the array"));
			}

		}

		for (auto* otherChar : otherChars)
		{
			if (!ensure(otherChar))
			{
				UE_LOG(LogTemp, Warning, TEXT("otherChar pointer is null."));
				return;

				///UE_LOG(LogTemp, Warning, TEXT("%s is overlapped with %s."), *otherChar->GetName(), *npc->GetName());
				///UE_LOG(LogTemp, Warning, TEXT("This npc's type is %s."), *thisChar->GetNPCType());
			}
			/*
			///Using movespeed of this ai as a parameter for when to stop checking distances of others
			///if ((thisChar->GetNPCType() != otherChar->GetNPCType()) && moveSpeed > 0.0) 
			//if (npc->GetNPCType() != otherChar->GetNPCType() && moveSpeed > 0.0)
				if (moveSpeed > 0.0)
			{
				///Find distance between this ai and each enemy in the overlapping actors array
				FVector distance;
				distance = npc->GetActorLocation() - otherChar->GetActorLocation();
				distanceLength = distance.Size();

				///UE_LOG(LogTemp, Warning, TEXT("The distance is %f"), distanceLength);

				if (distanceLength < 2000.0 && !targeted && !otherChar->targeted)
				{
					enemyTarget = otherChar;
					enemyTarget->targeted = true;
					enemyTarget->enemyTarget = npc;
					targeted = true;

					///UE_LOG(LogTemp, Warning, TEXT("The enemy: %s, is within distance"), *enemyTarget->GetName());

				} else if (otherChar->targeted && moveSpeed > 0.0)
				{
					///UE_LOG(LogTemp, Warning, TEXT("%s is already targeted"), *otherChar->GetName());
				}

				if (targeted)
				{
					moveSpeed = 0.0;
				}

			} /*else if (npc->GetNPCType() == otherChar->GetNPCType())
			{
				///UE_LOG(LogTemp, Warning, TEXT("%s is the same class as me: %s"), *otherChar->GetName(), *npc->GetName());

			}*/
		}

		//AddMovementInput(moveDirection, moveSpeed);
	}
	/*
	if (enemyTarget)
	{
		moveSpeed = 0.25;

		///Find distance between this ai and each enemy in the overlapping actors array
		FVector distance;
		distance = npc->GetActorLocation() - enemyTarget->GetActorLocation();
		targetDistanceLength = distance.Size();

		//TODO change from instant rotation to rotation over time
		//
		FRotator npcRotate = FRotationMatrix::MakeFromX(FVector(distance.X, distance.Y, 0)).Rotator();
		///npc->SetActorRotation(lerp from current rotation to new rotation of npcRotate);?
		///npc->SetActorRotation(distance.Rotation());
		///npc->SetActorRotation(npcRotate);
		npc->GetRootComponent()->SetWorldRotation(npcRotate);

		if (targetDistanceLength < 800.0)
		{
			moveSpeed = 0.0;
		}

		AddMovementInput(npc->GetActorForwardVector() * -1, moveSpeed);
	}*/
	
	
}
