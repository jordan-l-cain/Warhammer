// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPCMovementComponent.h"
#include "NPC_Controller.h"
#include "WorldEvents.h"
#include "WarhammerGameModeBase.h"

TArray<ANPC*> AWarhammerGameModeBase::LeaderList;

TArray<ANPC*> AWarhammerGameModeBase::dwarfEventList;
TArray<ANPC*> AWarhammerGameModeBase::greenskinEventList;
int AWarhammerGameModeBase::greenskinEventCount;
int AWarhammerGameModeBase::dwarfEventCount;


//TODO create a TMAP in both the dialogue and here for bools, each key will be a duplicate. At the end of a dialogue, run a function that will change each bool of the gamemode to equal that of the dialogue. Can also call events in this class, so we can check which bool is true and run the relevant event

void AWarhammerGameModeBase::SetDeadNPCs(ENPCRace race, int dead)
{
	if (race == ANPC::GetDwarfRace())
	{
		//UE_LOG(LogTemp, Warning, TEXT("increasing dead dwarfs"))
		deadDwarfs += dead;
	}
	if (race == ANPC::GetGreenskinRace())
	{
		//UE_LOG(LogTemp, Warning, TEXT("increasing dead greenskins"))
		deadGreenskins += dead;
	}

	if (deadDwarfs >= 10)
	{
		//AWorldEvents::FirstEvent(LeaderList, dwarfEventPositions, greenskinEventPositions);
	}
}

void AWarhammerGameModeBase::PopulateLeaderList()
{
	LeaderList.Empty();
	for (TActorIterator<ANPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ANPC *actor = *ActorItr;

		if (actor && actor->GetNPCType() == actor->GetChampionType())
		{
			if (!LeaderList.Contains(actor)  && actor->isLeader)
			{
				UE_LOG(LogTemp, Warning, TEXT("Adding %s to leader array."), *actor->GetName());
				LeaderList.Add(actor);
			}
		}
	}
	/*
	for (auto* actor : LeaderList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is a leader in the array."), *actor->GetName());
	}*/
}

void AWarhammerGameModeBase::SetTravelLocation(const ANPC* caller)
{
	SetTravelLocationEvent(caller);
}



void AWarhammerGameModeBase::ReplaceLeader(int32 indexOf, ANPC* replacement, ANPC* oldLeader)
{
	/*for (auto* actor : LeaderList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is a leader in the OLD array at index %f."), *actor->GetName(), LeaderList.Find(actor));
	}*/
	if (LeaderList.Num() > 0 && LeaderList.IsValidIndex(indexOf))
	{
		if (LeaderList.Contains(LeaderList[indexOf]) && LeaderList[indexOf] != replacement  && LeaderList[indexOf] == oldLeader)
		{
			UE_LOG(LogTemp, Warning, TEXT("Removing the leader at the index."));
			LeaderList.RemoveAt(indexOf, 1, false);
			UE_LOG(LogTemp, Warning, TEXT("Inserting the new leader at the index."));
			LeaderList.Insert(replacement, indexOf);
			UE_LOG(LogTemp, Warning, TEXT("Leader was replaced."));

		} else if (LeaderList[indexOf] != oldLeader)
		{
			UE_LOG(LogTemp, Warning, TEXT("Finding new index of the leader."));
			indexOf = LeaderList.Find(oldLeader);
			UE_LOG(LogTemp, Warning, TEXT("Removing the old leader at the new index."));
			LeaderList.RemoveAt(indexOf, 1, false);
			UE_LOG(LogTemp, Warning, TEXT("Inserting the new leader at the index."));
			LeaderList.Insert(replacement, indexOf);
		}
	}

	/*for (auto* actor : LeaderList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is a leader in the NEW array at index %f."), *actor->GetName(), LeaderList.Find(actor));
	}*/
}


void AWarhammerGameModeBase::SetBools(FName key, bool values)
{
	WorldConditions[key] = values;

	//Call events based on bools here

	if (WorldConditions[FName(TEXT("goodBool"))])
	{
		UE_LOG(LogTemp, Warning, TEXT("good bool is correct"));
		WorldConditions[FName(TEXT("goodBool"))] = false;
	}

	if ( WorldConditions[FName(TEXT("testBool"))] )
	{
		UE_LOG(LogTemp, Warning, TEXT("test bool is correct"));
		WorldConditions[FName(TEXT("testBool"))] = false;
		AWorldEvents::FirstEvent(LeaderList, dwarfEventPositions, greenskinEventPositions);
	}
	
}

void AWarhammerGameModeBase::EndEvent(ANPC* caller)
{
	//TODO create an overall event list that will check if the caller is containted, if not add? how to tell if all npc's are at event

	//if eventCount <= EventList.Num() then reset to 0
	

	if (caller->GetNPCRace() == caller->GetDwarfRace())
	{
		/*dwarfEventCount = 0;

		for (auto* dwarf : dwarfEventList)
		{
			if (dwarf->npcController->atEventPosition)
			{
				//TODO If this is changed to start event, we can check here for any npc's in the event list who are dead, and remove them. Would be better off having any npc that was headed to the event remove themselves from the array
				dwarfEventCount++;
			}

			UE_LOG(LogTemp, Warning, TEXT("Dwarf Event Count is %d, while the Event List Num() is %d"), dwarfEventCount, dwarfEventList.Num());

		}*/

		if (dwarfEventCount >= dwarfEventList.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("All dwarfs are at the event"));

			for (auto* dwarf : dwarfEventList)
			{
				dwarf->movementComponent->moveToLocation = true;
				dwarf->targetDestination = nullptr;
				dwarf->npcController->SetState(dwarf->npcController->GetIdleState());
				dwarf->movementComponent->curMoveState = dwarf->movementComponent->GetNullState();
			}

			dwarfEventList.Empty();
			dwarfEventCount = 0;
		}
	}

	if (caller->GetNPCRace() == caller->GetGreenskinRace())
	{
		/*
		greenskinEventCount = 0; 

		for (auto* greenskin : greenskinEventList)
		{
			if (greenskin->npcController->atEventPosition)
			{
				greenskinEventCount++;
			}

			UE_LOG(LogTemp, Warning, TEXT("Greenskin Event Count is %d, while the Event List Num() is %d"), greenskinEventCount, greenskinEventList.Num());

		}*/

		if (greenskinEventCount >= greenskinEventList.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("All greenskins are at the event"));

			//This for loop can be used to end the event
			for (auto* greenskin : greenskinEventList)
			{
				greenskin->movementComponent->moveToLocation = true;
				greenskin->targetDestination = nullptr;
				greenskin->npcController->SetState(greenskin->npcController->GetIdleState());
				greenskin->movementComponent->curMoveState = greenskin->movementComponent->GetNullState();
			}

			greenskinEventList.Empty();
			greenskinEventCount = 0;
		}
	}
}

void AWarhammerGameModeBase::RemoveFromEvent(ANPC * deadNPC)
{
	if (deadNPC->GetNPCRace() == deadNPC->GetDwarfRace() && dwarfEventList.Contains(deadNPC))
	{
		//TODO in new leaders, instead of removing the dead leader here, we can remove them there and immediately add the new leader to event list
		dwarfEventList.Remove(deadNPC);
		UE_LOG(LogTemp, Warning, TEXT("Removing %s to the dwarf Event List"), *deadNPC->GetName());
		EndEvent(deadNPC);

	} else if (deadNPC->GetNPCRace() == deadNPC->GetGreenskinRace() && greenskinEventList.Contains(deadNPC))
	{
		greenskinEventList.Remove(deadNPC);
		UE_LOG(LogTemp, Warning, TEXT("Removing %s to the greenskin Event List"), *deadNPC->GetName());
		EndEvent(deadNPC);
	}
}
