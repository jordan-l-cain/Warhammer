// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPCMovementComponent.h"


void UNPCMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UNPCMovementComponent::MoveAI(ANPC* npc, TArray<AActor*> OverlappingActors)
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
			///UE_LOG(LogTemp, Warning, TEXT("%s is overlapped with %s."), *actor->GetName(), *npc->GetName());
			///UE_LOG(LogTemp, Warning, TEXT("This npc's type is %s."), *thisChar->GetNPCType());

			if (!otherChars.Contains(actor))
			{
				otherChars.Add(Cast<ANPC>(actor));
				//TODO solve issue with capsule collider colliding with self's OverlapCollider (capsule collider is set not to generate overlap events)
				UE_LOG(LogTemp, Warning, TEXT("%s was added to %s's array"), *actor->GetName(), *npc->GetName());
			}
		}

		for (auto* otherChar : otherChars)
		{
			if (!ensure(otherChar))
			{
				UE_LOG(LogTemp, Warning, TEXT("otherChar pointer is null."));

			}
			
			///Using movespeed of this ai as a parameter for when to stop checking distances of others
			///if ((thisChar->GetNPCType() != otherChar->GetNPCType()) && moveSpeed > 0.0)
			if (npc->GetNPCType() != otherChar->GetNPCType() && moveSpeed > 0.0)
			{
				///Find distance between this ai and each enemy in the overlapping actors array
				FVector distance;
				distance = npc->GetActorLocation() - otherChar->GetActorLocation();
				distanceLength = distance.Size();

				///UE_LOG(LogTemp, Warning, TEXT("The distance is %f"), distanceLength);

				if (distanceLength < 2000.0 && !npc->movementComponent->targeted && !otherChar->movementComponent->targeted)
				{
					enemyTarget = otherChar;
					enemyTarget->movementComponent->targeted = true;
					enemyTarget->movementComponent->enemyTarget = npc;
					targeted = true;

					///UE_LOG(LogTemp, Warning, TEXT("The enemy: %s, is within distance"), *enemyTarget->GetName());

				} else if (otherChar->movementComponent->targeted && moveSpeed > 0.0)
				{
					///UE_LOG(LogTemp, Warning, TEXT("%s is already targeted"), *otherChar->GetName());
				}

				//This will handle interactions with NPCs of the same type
				if (npc->GetNPCType() == otherChar->GetNPCType())
				{
					///UE_LOG(LogTemp, Warning, TEXT("%s is the same class as me: %s"), *otherChar->GetName(), *npc->GetName());

				}
			}
		}

		npc->AddMovementInput(moveDirection, moveSpeed);
	}
	
	if (enemyTarget)
	{
		moveSpeed = 0.25;

		///Find distance between this ai and each enemy in the overlapping actors array
		FVector distance;
		distance = npc->GetActorLocation() - enemyTarget->GetActorLocation();
		targetDistanceLength = distance.Size();

		//TODO change from instant rotation to rotation over time
		FRotator npcRotate = FRotationMatrix::MakeFromX(FVector(distance.X, distance.Y, 0)).Rotator();
		///npc->SetActorRotation(lerp from current rotation to new rotation of npcRotate);?
		///npc->SetActorRotation(distance.Rotation());
		///npc->SetActorRotation(npcRotate);
		npc->GetRootComponent()->SetWorldRotation(npcRotate);

		if (targetDistanceLength < 500.0)
		{
			moveSpeed = 0.0;
		}

		npc->AddMovementInput(npc->GetActorForwardVector() * -1, moveSpeed);
	}
	
}
