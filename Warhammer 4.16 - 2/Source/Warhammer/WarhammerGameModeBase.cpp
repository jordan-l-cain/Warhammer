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

		if (actor->GetNPCType() == actor->GetChampionType())
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

void AWarhammerGameModeBase::ReplaceLeader(int32 indexOf, ANPC* replacement)
{
	/*for (auto* actor : LeaderList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is a leader in the OLD array at index %f."), *actor->GetName(), LeaderList.Find(actor));
	}*/
	if (LeaderList.Contains(LeaderList[indexOf]) && LeaderList[indexOf] != replacement)
	{
		LeaderList.RemoveAt(indexOf, 1, false);
		LeaderList.Insert(replacement, indexOf);
	}

	/*for (auto* actor : LeaderList)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is a leader in the NEW array at index %f."), *actor->GetName(), LeaderList.Find(actor));
	}*/
}
