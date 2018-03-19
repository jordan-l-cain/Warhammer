// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Locations.h"
#include "NPC.h"


// Sets default values
ALocations::ALocations()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALocations::BeginPlay()
{
	Super::BeginPlay();
	//TODO set probabilities to random numbers

	dwarfProbability += FMath::RandRange(0, 30);
	greenskinProbability += FMath::RandRange(0, 30);
}

// Called every frame
void ALocations::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//TODO function for checking when someone arrives, raises opposite race's probability
//TODO for adding/removing npc's from an array to determine when to increase/decrease probability

ALocations* ALocations::GetDestination(ALocations* currentLocation, bool dwarf)
{
	/*
	
	find a location that is not this location
	base this on a locations probability, which is based on who is there as well as what race controls it
	
	run through all actors of this class
		if the probability of this class is higher than the last class
			set this class as the target destination
			set this probabililty as the temp number for comparing the rest

	return target destination
	*/
	int highProb = 0;
	ALocations* nextLocation = currentLocation;

	if (dwarf)
	{
		currentLocation->greenskinProbability -= 7;

	} else
	{
		currentLocation->dwarfProbability -= 7;
	}

	UE_LOG(LogTemp, Warning, TEXT("The NPC's current location is %s."), *currentLocation->name.ToString());

	for (TActorIterator<ALocations> location(currentLocation->GetWorld()); location; ++location)
	{
		if (location->location != ELocation::WAYPOINT && location->location != currentLocation->location)
		{
			if (dwarf)
			{
				UE_LOG(LogTemp, Warning, TEXT("This location is %s odds are %d"), *location->name.ToString(), location->dwarfProbability);

				if (location->dwarfProbability > highProb)
				{
					nextLocation = *location;
					highProb = location->dwarfProbability;
				}
			} else
			{
				UE_LOG(LogTemp, Warning, TEXT("This location is %s odds are %d"), *location->name.ToString(), location->greenskinProbability);

				if (location->greenskinProbability > highProb)
				{
					nextLocation = *location;
					highProb = location->greenskinProbability;
				}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%s is the destination"), *nextLocation->name.ToString());
	return nextLocation;
}

void ALocations::nextWaypoint(ANPC* npc)
{
	/*
	if the index of the previous location's array ( which is the waypoint's location in the array ) is less than the number of indices
	then increase the index, and make the value of that new index the next waypoint, then move to
	else, set the target destination to null since we are there
	*/
	UE_LOG(LogTemp, Warning, TEXT("%s is checking for next waypoint"), *npc->GetName());
	int index = npc->previousLocation->locationArrays[npc->targetDestination->location].locations.Find(npc->waypoint);

	if (index < npc->previousLocation->locationArrays[npc->targetDestination->location].locations.Num() - 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s setting next waypoint from array"), *npc->GetName());
		npc->currentLocation = npc->previousLocation->locationArrays[npc->targetDestination->location].locations[index];
		index++;
		npc->waypoint = npc->previousLocation->locationArrays[npc->targetDestination->location].locations[index];

	} else
	{

		npc->currentLocation = npc->previousLocation->locationArrays[npc->targetDestination->location].locations[index];

		if (npc->GetNPCRace() == ANPC::GetDwarfRace())
		{
			npc->currentLocation->greenskinProbability += 7;
		
		} else
		{
			npc->currentLocation->dwarfProbability += 7;
		}
		UE_LOG(LogTemp, Warning, TEXT("%s is at final location, %s"), *npc->GetName(), *npc->currentLocation->name.ToString());
		npc->targetDestination = nullptr;
	}
}


