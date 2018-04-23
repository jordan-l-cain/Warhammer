// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPCMovementComponent.h"
#include "ActivityObject.h"
#include "Locations.h"



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


	/*
		TODO How to handle timers?
		TODO create npc variables
		TODO account for npc or player already at activity
		TODO account for interrupting activities
		TODO if already at activity, can't do same activity

		activities are individual timers, which will determine when the npc goes to new event
			activity calls end activity event on npc
				one called, animation montage has event that will trigger at end of finish animation
					sets activity to unoccupied and gets npc a new activity


		if location has npcs and activities
			if not in activity
				set them to go to new activity
				in npc controller set bool, one once they head off to activity and one when they get there, which will start the timer from when they'll go elsewhere
				Give personality tag to each, which determines what activities they can participate in
			if no activity available
				go to home and wait for next timer
	
	*/


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

void ALocations::AddNPC(ANPC * npc)
{
	if (!locationNPCs.Contains(npc))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is adding %s"), *name.ToString(), *npc->GetName());
		locationNPCs.Add(npc);
	}

	if (!npc->activity)
	{
		GetActivity(npc);
	}
}

void ALocations::GetActivity(ANPC * npc)
{
	bool drunk = false;
	bool library = false;
	bool street = false;
	bool vendor = false;
	bool customer = false;

	bool previousDrunk = false;
	bool previousLibrary = false;
	bool previousStreet = false;
	bool previousVendor = false;

	if (npc->activity)
	{
		npc->activity->occupied = false;
		npc->previousActivity = npc->activity;
		npc->activity = nullptr;
	}

	if(npc->previousActivity)
	{ 

		if (drunkActivities.Contains(npc->previousActivity))
		{
			UE_LOG(LogTemp, Warning, TEXT("Previously drunk at %s"), *npc->previousActivity->GetName());
			previousDrunk = true;

		} else if (libraryActivities.Contains(npc->previousActivity))
		{
			UE_LOG(LogTemp, Warning, TEXT("Previously library at %s"), *npc->previousActivity->GetName());
			previousLibrary= true;

		} else if (streetActivities.Contains(npc->previousActivity))
		{
			UE_LOG(LogTemp, Warning, TEXT("Previously street at %s"), *npc->previousActivity->GetName());
			previousStreet = true;

		} else if (vendorActivities.Contains(npc->previousActivity))
		{
			UE_LOG(LogTemp, Warning, TEXT("Previously market at %s"), *npc->previousActivity->GetName());
			previousVendor = true;

		}
	}

	if (npc->personalityTags.Num() > 0)
	{
		for (auto tag : npc->personalityTags)
		{
			if (tag == ANPC::drink && !previousDrunk)
			{
				UE_LOG(LogTemp, Warning, TEXT("drunk"));
				drunk = true;
			}

			if (tag == ANPC::library && !previousLibrary)
			{
				UE_LOG(LogTemp, Warning, TEXT("library"));
				library = true;
			}

			if (tag == ANPC::street && !previousStreet)
			{
				UE_LOG(LogTemp, Warning, TEXT("street"));
				street = true;
			}

			if (tag == ANPC::vendor && !previousVendor)
			{
				UE_LOG(LogTemp, Warning, TEXT("vendor"));
				vendor = true;
			}

			if (tag == ANPC::customer)
			{
				UE_LOG(LogTemp, Warning, TEXT("customer"));
				customer = true;
			}
		}

		int i = FMath::RandRange(0, 4);

		if (i == 0 && drunk)
		{
			if (drunkActivities.Num() > 0)
			{
				int a = FMath::RandRange(0, drunkActivities.Num() - 1);

				if (!drunkActivities[a]->occupied)
				{
					npc->activity = drunkActivities[a];
					npc->activity->occupied = true;
					return;

				} else
				{
					GetActivity(npc);
					return;
				}
			}

		} else if (i == 1 && library)
		{
			if (libraryActivities.Num() > 0)
			{
				int a = FMath::RandRange(0, libraryActivities.Num() - 1);

				if (!libraryActivities[a]->occupied)
				{
					npc->activity = libraryActivities[a];
					npc->activity->occupied = true;
					return;

				} else
				{
					GetActivity(npc);
					return;
				}
			}

		} else if (i == 2 && street)
		{
			if (streetActivities.Num() > 0)
			{
				int a = FMath::RandRange(0, streetActivities.Num() - 1);

				if (!streetActivities[a]->occupied)
				{
					npc->activity = streetActivities[a];
					npc->activity->occupied = true;
					return;

				} else
				{
					GetActivity(npc);
					return;
				}
			}

		} else if (i == 3 && vendor)
		{
			if (vendorActivities.Num() > 0)
			{
				int a = FMath::RandRange(0, vendorActivities.Num() - 1);

				if (!vendorActivities[a]->occupied)
				{
					npc->activity = vendorActivities[a];
					npc->activity->occupied = true;
					return;

				} else
				{
					GetActivity(npc);
					return;
				}
			}

		} else if (i == 4 && customer)
		{
			if (customerActivities.Num() > 0)
			{
				int a = FMath::RandRange(0, customerActivities.Num() - 1);

				if (!customerActivities[a]->occupied)
				{
					npc->activity = customerActivities[a];
					npc->activity->occupied = true;
					return;

				} else
				{
					GetActivity(npc);
					return;
				}
			}
		} else
		{
			GetActivity(npc);
		}
	}
}





