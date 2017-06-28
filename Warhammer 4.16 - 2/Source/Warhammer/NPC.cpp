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

void ANPC::ModHealth(float modifier)
{
	if (npcHealth > 0)
	{
		npcHealth += modifier;
		UE_LOG(LogTemp, Warning, TEXT("%s's health is %f"), *npc->GetName(), npcHealth);

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
