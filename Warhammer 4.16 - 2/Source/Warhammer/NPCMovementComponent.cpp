// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPCMovementComponent.h"


void UNPCMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	originalSpeed = moveSpeed;
	originalRotation = GetOwner()->GetActorRotation();
}

void UNPCMovementComponent::MoveAI(ANPC* npc, TArray<AActor*> OverlappingActors)
{

	if (!enemyTarget)
	{
		if (ensure(npc))
		{
			moveDirection = npc->GetActorForwardVector();
			npc->GetRootComponent()->SetWorldRotation(originalRotation);

		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("npc pointer is null."));
			return;
		}

		//TODO optimize for large numbers, Only add npc's to array, and only up to 5? Need way to remove when they're dead as well
		for (auto* actor : OverlappingActors)
		{
			///UE_LOG(LogTemp, Warning, TEXT("%s is overlapped with %s."), *actor->GetName(), *npc->GetName());
			///UE_LOG(LogTemp, Warning, TEXT("This npc's type is %s."), *thisChar->GetNPCType());

			if (!otherChars.Contains(actor))
			{
				otherChars.Add(Cast<ANPC>(actor));
				//TODO solve issue with capsule collider colliding with self's OverlapCollider (capsule collider is set not to generate overlap events)
				///UE_LOG(LogTemp, Warning, TEXT("%s was added to %s's array"), *actor->GetName(), *npc->GetName());
			}
		}

		if (otherChars.Max() > 0)
		{
			for (auto* otherChar : otherChars)
			{
				/*
				if (otherChar->isDead)
				{
					int deleteCharIndex;
					deleteCharIndex = otherChars.Find(otherChar);
					otherChars.RemoveAt(deleteCharIndex);
					if (!otherChars.Contains(otherChar))
					{
						///UE_LOG(LogTemp, Warning, TEXT("otherChar is no longer in the array"));
					}
				}*/

				//Confrontation is used to check when this npc is about to fight someone, will be used to ensure this npc stops checking distances
				if (npc->GetNPCType() != otherChar->GetNPCType() && !confrontation)
				{
					///Find distance between this ai and each enemy in the overlapping actors array
					FVector distance;
					distance = npc->GetActorLocation() - otherChar->GetActorLocation();
					distanceLength = distance.Size();

					///UE_LOG(LogTemp, Warning, TEXT("The distance is %f"), distanceLength);

					if (distanceLength < 3000.0 && !npc->movementComponent->targeted && !otherChar->movementComponent->targeted)
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
		}

		npc->AddMovementInput(moveDirection, moveSpeed);
	}
	
	if (enemyTarget)
	{
		moveSpeed = 0.75;

		///Find distance between this ai and each enemy in the overlapping actors array
		FVector distance;
		distance = npc->GetActorLocation() - enemyTarget->GetActorLocation();
		targetDistanceLength = distance.Size();

		//TODO change from instant rotation to rotation over time
		FRotator npcRotate = FRotationMatrix::MakeFromX(FVector(distance.X * -1, distance.Y * -1, 0)).Rotator();
		///npc->SetActorRotation(lerp from current rotation to new rotation of npcRotate);?
		npc->GetRootComponent()->SetWorldRotation(npcRotate);

		if (targetDistanceLength < 400.0)
		{
			moveSpeed = 0.0;
			confrontation = true;
		}

		npc->AddMovementInput(npc->GetActorForwardVector(), moveSpeed);
	}
	
}

