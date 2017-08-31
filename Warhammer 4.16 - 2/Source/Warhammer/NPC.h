// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

class UNPCMovementComponent;
class ANPC_Controller;
class AWarhammerGameModeBase;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ENPCRace : uint8
{
	Dwarf UMETA(DisplayName = "Dwarf"),
	Greenskin UMETA(DisplayName = "Greenskin"),
	Enemy	UMETA(DisplayName = "Enemy")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ENPCType : uint8
{
	CHAMPION UMETA(DisplayName = "Champion"),
	COMMON UMETA(DisplayName = "Common")
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


	bool dwarf = false;
	bool greenskin = false;

	//NPC Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	float npcHealth;

	//Strength Stat, which determines amount of damage done to enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	float strength;

	//Attack Stat, which determines who is more likely to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	float attack;

	//Defense Stat, which determines blocking/dodging capability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	float defense;

	//Number of kills this npc has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	float killCount;

	//Boolean that determines who can attack, read/set by combat class 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	bool canAttack = false;

	//Read function for canAttack boolean
	bool GetCanAttack();

	//Boolean that determines who can attack, read/set by combat class 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	bool attacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Boolean used to check if NPC is considered a leader
	bool isLeader = false;

	//Boolean used to determine if this npc is dead.
	bool isDead = false;

	//Function that adjusts npc health
	void ModHealth(float modifier);

	//Set function for canAttack boolean
	void ModCanAttack(bool boolean);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Movement Component
	UNPCMovementComponent* movementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//AI Controller
	ANPC_Controller* npcController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Enum used to set a npc type that is readable by the movement script, so it may determine it's actions
	ENPCRace npcRace;

	UFUNCTION(BlueprintPure)
	// Return function that will allow the movement script to determine the npc type
	ENPCRace GetNPCRace();

	UFUNCTION(BlueprintPure)
	// Returns ENPCRace of Dwarf for comparison
	ENPCRace GetDwarfRace();

	UFUNCTION(BlueprintPure)
	// Returns ENPCRace of Dwarf for comparison
	ENPCRace GetGreenskinRace();

	// Returns ENPCRace of Dwarf for comparison
	ENPCRace GetEnemyRace();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Enum used to set the type this NPC is
	ENPCType npcType;

	// Returns the ENPCType
	ENPCType GetNPCType();

	// Returns ENPCType of Champion for comparison
	ENPCType GetChampionType();

	// Returns ENPCType of Common for comparison
	ENPCType GetCommonType();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//This instance of ANPC
	ANPC* npc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//ANPC variable used to store this npc's leader, if it has one
	ANPC* leader;

	//ANPC variable used to store the replacement leader.
	ANPC* replacementLeader = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//This array is used only by a leader to find and set followers
	TArray<ANPC*> followers;

	//Location used to set the center of a battle between two goups
	FVector battleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	AActor* waypoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
	//This array is used to store and access all attack animations
	TArray<UAnimMontage*> attackAnims;

	//This function is used to call the Attack Animation event since it can only be called from this class.
	void CallMoveStateEvent();

	UFUNCTION(Category = "States", BlueprintImplementableEvent)
	//Determines when the Anim blueprint can play the movement animations. Called in NPC_Controller_BP
	void inMoveState();

	UFUNCTION(Category = "States", BlueprintImplementableEvent)
	void inAttackState();

	//This function is used to call the Attack Animation event since it can only be called from this class.
	void CallAttackAnimationEvent(int i);

	//This function is used to call the Attack Animation event since it can only be called from this class.
	void CallDefenseAnimationEvent(int i);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayAttackAnimation(int i);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayDefenseAnimation(int i);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
