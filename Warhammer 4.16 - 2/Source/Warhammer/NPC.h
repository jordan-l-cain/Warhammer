// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

class UNPCMovementComponent;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ENPCClass : uint8
{
	Dwarf1 UMETA(DisplayName = "Dwarf"),
	Greenskin1 UMETA(DisplayName = "Greenskin"),
	Enemy1	UMETA(DisplayName = "Enemy")
};

/**
* This class will set up all NPC specific values as well as instances of actors
*/
UCLASS(Blueprintable)
class WARHAMMER_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//NPC Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	float npcHealth;

	//TODO change to a float value affected by stats?
	//Boolean that determines who can attack, read/set by combat class 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Settings")
	bool canAttack = false;

	//Function that adjusts npc health
	void ModHealth(float modifier);

	//Set function for canAttack boolean
	void ModCanAttack(bool boolean);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Array used to store all nearby actors
	TArray<AActor*> OverlappingActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Movement Component
	UNPCMovementComponent* movementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Enum used to set a npc type that is readable by the movement script, so it may determine it's actions
	ENPCClass npcType;

	// Return function that will allow the movement script to determine the npc type
	ENPCClass GetNPCType();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//This instance of ANPC
	ANPC* npc;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Read function for canAttack boolean
	bool GetCanAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
