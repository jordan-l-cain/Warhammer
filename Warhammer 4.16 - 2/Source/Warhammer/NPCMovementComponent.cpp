// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPC_Controller.h"
#include "WarhammerGameModeBase.h"
#include "NPCMovementComponent.h"


void UNPCMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	originalRotation = GetOwner()->GetActorRotation();
}

void UNPCMovementComponent::MoveAI(ANPC* npc, TArray<AActor*> OverlappingActors)
{
	switch (curMoveState)
	{
		case EMoveStates::FOLLOW:
			Follow(npc);
			break;

		case EMoveStates::MOVETOENEMY:
			MoveToEnemy(npc, OverlappingActors);
			break;

		case EMoveStates::MOVETOLOCATION:
			MoveToLocation();
			break;

		case EMoveStates::NULLMOVE:
			curMoveState = defaultState;
	}

	//TODO create defaultstate function, so that different npc's can have different defaults to call to out of the npc controller, and so they can change what state they switch to
	
}

void UNPCMovementComponent::Follow(ANPC* npc)
{
	///UE_LOG(LogTemp, Warning, TEXT("The npc is in the follow state"));
	MaxWalkSpeed = 750;

	timer++;

	if (npc->leader )
	{
		
		if (followerIndex < 4)
		{
			FVector formationPosition = FVector( npc->leader->GetActorLocation().X - 10, (npc->leader->GetActorLocation().Y - 300) + (followerIndex * 300), npc->leader->GetActorLocation().Z );
			FVector distanceToPosition = npc->GetActorLocation() - formationPosition;
			MaxWalkSpeed = (distanceToPosition.Size() + npc->leader->movementComponent->Velocity.X) * .35;
			
			if (timer >= 35)
			{
				npc->npcController->MoveToLocation(formationPosition);
				timer = 0;
			}
		}

		if (npc->leader->movementComponent->confrontation)
		{
			curMoveState = EMoveStates::MOVETOENEMY;
		}

	} else if(!npc->leader)
	{
		UE_LOG(LogTemp, Warning, TEXT("The common npc does not have a leader"));
	}
}

void UNPCMovementComponent::MoveToEnemy(ANPC* npc, TArray<AActor*> OverlappingActors)
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
			///UE_LOG(LogTemp, Warning, TEXT("This npc's type is %s."), *thisChar->GetNPCRace());

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
				//TODO Do I need to remove characters from otherChar array?
				/*
				if (otherChar->isDead)
				{
				UE_LOG(LogTemp, Warning, TEXT("Removing char from otherChars"))
				int deleteCharIndex;
				deleteCharIndex = otherChars.Find(otherChar);
				otherChars.RemoveAt(deleteCharIndex);
				if (!otherChars.Contains(otherChar))
				{
				///UE_LOG(LogTemp, Warning, TEXT("otherChar is no longer in the array"));
				}
				}*/

				//Confrontation is used to check when this npc is about to fight someone, will be used to ensure this npc stops checking distances
				if (npc->GetNPCRace() != otherChar->GetNPCRace() && !confrontation && !otherChar->isDead)
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

					} else if (otherChar->movementComponent->targeted && canMove)
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s is already targeted"), *otherChar->GetName());
					}

					//This will handle interactions with NPCs of the same type
					if (npc->GetNPCRace() == otherChar->GetNPCRace())
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s is the same class as me: %s"), *otherChar->GetName(), *npc->GetName());

					}
				}
			}
		}

		///UE_LOG(LogTemp, Warning, TEXT("npc should be moving"));
		FVector forwardLocation;
		forwardLocation += npc->GetActorLocation() + (npc->GetActorForwardVector() * 500);
		//npc->npcController->MoveToLocation(forwardLocation);
		npc->AddMovementInput(npc->GetActorForwardVector(), 10);
		MaxWalkSpeed = 400;
	}

	if (enemyTarget)
	{

		///Find distance between this ai and each enemy in the overlapping actors array
		FVector distance;
		distance = npc->GetActorLocation() - enemyTarget->GetActorLocation();
		targetDistanceLength = distance.Size();


		if (targetDistanceLength < 400.0)
		{
			canMove = false;
			confrontation = true;
		}

		//npc->AddMovementInput(npc->GetActorForwardVector(), moveSpeed);
		if (ensure(npc->npcController))
		{
			MaxWalkSpeed = targetDistanceLength * .35;
			//TODO change moveto to call once
			npc->npcController->MoveToActor(enemyTarget, 150.0);
		}
	}
}

void UNPCMovementComponent::MoveToLocation()
{
	//TODO add calculating distances of each enemy leader in the list, can call only every 2-5 seconds
}

EMoveStates UNPCMovementComponent::GetFollowState()
{
	return EMoveStates::FOLLOW;
}

EMoveStates UNPCMovementComponent::GetMoveToEnemyState()
{
	return EMoveStates::MOVETOENEMY;
}

EMoveStates UNPCMovementComponent::GetMoveToLocationState()
{
	return EMoveStates::MOVETOLOCATION;
}

void UNPCMovementComponent::SetDefaultState(EMoveStates state)
{
	defaultState = state;
}

