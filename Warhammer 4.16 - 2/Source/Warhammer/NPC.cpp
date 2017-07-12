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
	if (npcType == ENPCType::Dwarf)
	{
		dwarf = true;
	}
	if (npcType == ENPCType::Greenskin)
	{
		greenskin = true;
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

ENPCType ANPC::GetNPCType()
{
	return npcType;
}

ENPCType ANPC::GetDwarfType()
{
	return ENPCType::Dwarf;
}

ENPCType ANPC::GetGreenskinType()
{
	return ENPCType::Greenskin;
}

ENPCType ANPC::GetEnemyType()
{
	return ENPCType::Enemy;
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
