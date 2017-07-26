// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "WarhammerGameModeBase.h"

TArray<ANPC*> AWarhammerGameModeBase::LeaderList;
///int AWarhammerGameModeBase::deadDwarfs;
///int AWarhammerGameModeBase::deadGreenskins;

void AWarhammerGameModeBase::PrintKills(int a, int b)
{
	UE_LOG(LogTemp, Warning, TEXT("Number of dead dwarfs: %f."), a);
	UE_LOG(LogTemp, Warning, TEXT("Number of dead greenskins: %f."), b)
}

void AWarhammerGameModeBase::PopulateLeaderList()
{

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
}
