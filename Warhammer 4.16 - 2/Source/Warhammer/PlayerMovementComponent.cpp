// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Player_Char.h"
#include "NPC.h"
#include "PlayerMovementComponent.h"


void UPlayerMovementComponent::MovementState()
{
	if (Enemies.Num() > 0)
	{
		for (auto* enemy : Enemies)
		{
			FVector distance;
			distance = GetActorLocation() - enemy->GetActorLocation();
			float targetDistanceLength = distance.Size();

			if (targetDistanceLength < 1000)
			{
				//UE_LOG(LogTemp, Warning, TEXT("%s is within 10 meters."), *enemy->GetName());
			}
		}
	}
}

void UPlayerMovementComponent::FilterEnemies(const TArray<AActor*> npcs, APlayer_Char* playerChar)
{
	for (auto* enemy : npcs)
	{
		ANPC* actor = Cast<ANPC>(enemy);

		if (ensure(actor) && ((actor->GetNPCRace() == actor->GetDwarfRace()) && (playerChar->GetPlayerRace() == playerChar->GetGreenskinRace()) || (actor->GetNPCRace() == actor->GetGreenskinRace()) && (playerChar->GetPlayerRace() == playerChar->GetDwarfRace())) && !actor->isDead)
		{
			if (!Enemies.Contains(actor))
			{
				Enemies.Add(Cast<ANPC>(actor));
				//TODO solve issue with capsule collider colliding with self's OverlapCollider (capsule collider is set not to generate overlap events)
				//UE_LOG(LogTemp, Warning, TEXT("%s was added to %s's array"), *actor->GetName(), *playerChar->GetName());
			}
		}
	}
}



