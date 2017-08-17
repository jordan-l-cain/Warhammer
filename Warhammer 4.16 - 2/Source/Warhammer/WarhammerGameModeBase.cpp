// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "WarhammerGameModeBase.h"

TArray<ANPC*> AWarhammerGameModeBase::LeaderList;

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
