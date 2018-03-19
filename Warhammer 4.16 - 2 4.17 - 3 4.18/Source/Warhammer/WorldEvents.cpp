// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPC_Controller.h"
#include "WorldEvents.h"

// Sets default values
AWorldEvents::AWorldEvents()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldEvents::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldEvents::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldEvents::FirstEvent(TArray<ANPC*> Leaders, TArray<AActor*> dwarfPositions, TArray<AActor*> greenskinPositions)
{

	//Change to non static, make a reference to this class in gamemode to call event functions?


	
	//foreach leader have an array of locations for them to move to
	//when all leaders are at their location, start the event dialogues/animations on the main leaders

	int positionIndex = 0;

	for (auto* leader : Leaders)
	{
		//TODO figure out how to call this on leaders who are in the middle of a fight after they have finished

		UE_LOG(LogTemp, Warning, TEXT("%s is the leader about to call enter event"), *leader->GetName());
		//in the leaders list seperate the main leaders of each race
		//iterate through leaders and seperate them by race
	
		if (leader->GetNPCRace() == ANPC::GetDwarfRace() && !leader->isDead)
		{
			//TODO will need two seperate arrays for dwarfs and greenskins
			//for loop that will iterate through all leaders and assign them a location and to an array
			if (positionIndex <= dwarfPositions.Num() && dwarfPositions.IsValidIndex(positionIndex))
			{
				//If the position isn't vacant, then we increase the index to check the next position
				for (auto* position : dwarfPositions)
				{
					leader->npcController->PositionVacant(dwarfPositions[positionIndex]);

					if (!leader->npcController->vacant)
					{
						///UE_LOG(LogTemp, Warning, TEXT("vacancy is not true, increasing index"));
						positionIndex++;

					} else
					{
						leader->npcController->OccupyPosition(dwarfPositions[positionIndex]);
						leader->npcController->EnterEvent(dwarfPositions[positionIndex], dwarfPositions);
						UE_LOG(LogTemp, Warning, TEXT("%s is going to %s"), *leader->GetName(), *position->GetName());
						break;
					}
				}
			} else
			{
				UE_LOG(LogTemp, Warning, TEXT("The index of %d for event positions is not valid for %s"), positionIndex, *leader->GetName());
			}
		}

		if (leader->GetNPCRace() == ANPC::GetGreenskinRace() && !leader->isDead)
		{
			//TODO will need two seperate arrays for dwarfs and greenskins
			//for loop that will iterate through all leaders and assign them a location and to an array
			if (positionIndex <= greenskinPositions.Num() && greenskinPositions.IsValidIndex(positionIndex))
			{
				//If the position isn't vacant, then we increase the index to check the next position
				for (auto* position : greenskinPositions)
				{
					leader->npcController->PositionVacant(greenskinPositions[positionIndex]);

					if (!leader->npcController->vacant)
					{
						///UE_LOG(LogTemp, Warning, TEXT("vacancy is not true, increasing index"));
						positionIndex++;

					} else
					{
						leader->npcController->OccupyPosition(greenskinPositions[positionIndex]);
						leader->npcController->EnterEvent(greenskinPositions[positionIndex], greenskinPositions);
						UE_LOG(LogTemp, Warning, TEXT("%s is going to %s"), *leader->GetName(), *position->GetName());
						break;
					}
				}
			} else
			{
				UE_LOG(LogTemp, Warning, TEXT("The index of %d for event positions is not valid for %s"), positionIndex, *leader->GetName());
			}


			//timer that will choose two indices and trigger a whispered conversation between them about the event
		}
	}
}

