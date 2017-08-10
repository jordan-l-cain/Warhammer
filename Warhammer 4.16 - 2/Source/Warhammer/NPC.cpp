// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPCMovementComponent.h"
#include "NPC.h"


// Sets default values
ANPC::ANPC(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer.SetDefaultSubobjectClass<UNPCMovementComponent>(ACharacter::CharacterMovementComponentName)) 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	if (npcRace == ENPCRace::Dwarf)
	{
		dwarf = true;

		if (GetNPCType() == GetChampionType())
		{
			for (TActorIterator<ANPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ANPC *actor = *ActorItr;

				if ((actor->GetNPCRace() == actor->GetDwarfRace()) && (actor->GetNPCType() == actor->GetCommonType()))
				{
					if (!followers.Contains(actor) && followers.Num() < 3 && !actor->leader)
					{
						UE_LOG(LogTemp, Warning, TEXT("%s: Adding %s to my array."), *npc->GetName(), *actor->GetName());
						actor->leader = npc;
						followers.Add(actor);
						actor->movementComponent->followerIndex = followers.Find(actor);
					}
				}
			}
		}
	}

	if (npcRace == ENPCRace::Greenskin)
	{
		greenskin = true;

		if (GetNPCType() == GetChampionType())
		{
			for (TActorIterator<ANPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ANPC *actor = *ActorItr;

				if ((actor->GetNPCRace() == actor->GetGreenskinRace()) && (actor->GetNPCType() == actor->GetCommonType()))
				{
					if (!followers.Contains(actor) && followers.Num() < 3 && !actor->leader)
					{
						UE_LOG(LogTemp, Warning, TEXT("%s: Adding %s to my array."), *npc->GetName(), *actor->GetName());
						actor->leader = npc;
						followers.Add(actor);
					}
				}
			}
		}
	}
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

ENPCRace ANPC::GetNPCRace()
{
	return npcRace;
}

ENPCRace ANPC::GetDwarfRace()
{
	return ENPCRace::Dwarf;
}

ENPCRace ANPC::GetGreenskinRace()
{
	return ENPCRace::Greenskin;
}

ENPCRace ANPC::GetEnemyRace()
{
	return ENPCRace::Enemy;
}

ENPCType ANPC::GetNPCType()
{
	return npcType;
}

ENPCType ANPC::GetChampionType()
{
	return ENPCType::CHAMPION;
}

ENPCType ANPC::GetCommonType()
{
	return ENPCType::COMMON;
}

void ANPC::ModHealth(float modifier)
{
	if (npcHealth > 0)
	{
		npcHealth += modifier;
		///UE_LOG(LogTemp, Warning, TEXT("%s's health is %f"), *npc->GetName(), npcHealth);
	}

	if (npcHealth <= 0)
	{
		npcHealth = 0;
	}
}

void ANPC::ModCanAttack(bool boolean)
{
	canAttack = boolean;
}

bool ANPC::GetCanAttack()
{
	return canAttack;
}

void ANPC::CallMoveStateEvent()
{
	inMoveState();
}

void ANPC::CallAttackAnimationEvent(int i)
{
	PlayAttackAnimation(i);
}

void ANPC::CallDefenseAnimationEvent(int i)
{
	PlayDefenseAnimation(i);
}


/*

	//npc has two enums, race and type
		//type denotes whether the NPC is a champion, or a common npc

	//boolean determing whether an NPC is a leader or follower
		//standalone from the leader variable so leaders can also follow a leader, and can set different distances apart

	//ENPC variable to store this npc's leader
		//if leader is not null, then set move state to follow

	//leader array
		// only used when npc becomes a leader

*/
