// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

class UNPCMovementComponent;
class ANPC_Controller;
class AWarhammerGameModeBase;
class APlayer_Char;
class ALocations;
class AActivityObject;

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
	COMMON UMETA(DisplayName = "Common"),
	COMMONER UMETA(DisplayName = "Commoner")
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

	//NPC Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	FText Name;

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

	//Combat stance of the NPC
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Settings")
	int stance = 0;

	//Number of kills this npc has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	float killCount;

	//Boolean that determines who can attack, read/set by combat class, used to determine who does damage, and when to call combat::attack in npc_controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	bool canAttack = true;

	//Boolean that determines if both npc and enemy are in combat array and ready to attack if true for each. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	bool attacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Boolean used to check if NPC is considered a leader
	bool isLeader = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Boolean used to determine if this npc is dead.
	bool isDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Boolean used for blocking to keep from damaging health
	bool blocking = false;

	//Boolean used to determine if npc is at and participating in an activity
	bool inActivity = false;

	//Function that adjusts npc health
	void ModHealth(float modifier);

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
	static ENPCRace GetDwarfRace();

	UFUNCTION(BlueprintPure)
	// Returns ENPCRace of Greenskin for comparison
	static ENPCRace GetGreenskinRace();

	// Returns ENPCRace of Enemy for comparison
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

	// Returns ENPCType of Commoner for comparison
	ENPCType GetCommonerType();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//This instance of ANPC
	ANPC* npc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//ANPC variable used to store this npc's leader, if it has one
	ANPC* leader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//ANPC variable used to store this npc's leader for the player
	APlayer_Char* playerLeader;

	//ANPC variable used to store the replacement leader.
	ANPC* replacementLeader = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//This array is used only by a leader to find and set followers
	TArray<ANPC*> followers;

	//This int will indicate the number of followers an npc has, used in MoveToBattle to see how many have died.
	int followerCount;

	//Location used to set the center of a battle between two goups
	FVector battleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
	//This array is used to store and access all attack animations
	TArray<UAnimMontage*> attackAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
	//This array is used to store and access all block animations
	TArray<UAnimMontage*> blockAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
	//This array is used to store and access all npc hit animations
	TArray<UAnimMontage*> hitAnims;

	//This function is used to call the Attack Animation event since it can only be called from this class.
	void CallMoveStateEvent();

	UFUNCTION(Category = "States", BlueprintImplementableEvent)
	//Determines when the Anim blueprint can play the movement animations. Called in NPC_Controller_BP
	void inMoveState();

	UFUNCTION(Category = "States", BlueprintImplementableEvent)
	void inAttackState();

	//Function that returns the length of the attack array, so UCombat::Attack can determine the RandRange max Lines 54/59
	UFUNCTION(BlueprintImplementableEvent)
	int GetAnimNum(int set);

	//This function is used to call the Attack Animation event since it can only be called from this class.
	void CallAttackAnimationEvent(int weapon, int animation);

	//This function is used to call the Blocked Animation event since it can only be called from this class.
	void CallBlockedAnimationEvent(int weapon, int animation);

	//This function is used to call the Defense Animation event since it can only be called from this class.
	void CallDefenseAnimationEvent(int weapon, int animation);

	//This function is used to call the Hit Animation event since it can only be called from this class.
	void CallHitAnimationEvent(int weapon, int animation);

	//This function is used to call the Hit Animation event since it can only be called from this class.
	void CallDeathAnimationEvent(int weapon, int animation);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayAttackAnimation(int weapon, int animation);
	
	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayBlockedAnimation(int weapon, int animation);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayDefenseAnimation(int weapon, int animation);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayHitAnimation(int weapon, int animation);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayDeathAnimation(int weapon, int animation);

	//TODO Keep? Or should I just make individual animations for getting hit, and blocking
	//Function for npc's that, in blueprint, waits for the finish section of the current attack montage of enemy to play hit animation
	UFUNCTION(BlueprintImplementableEvent)
	void WaitForHit(ANPC* enemy, int weapon, int animation);

	//Event that will create dialogue widget
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void CreateDialogue();

	//Function that will end a dialogue and reset the npc
	UFUNCTION(BlueprintCallable, Category = "Functions")
	void EndDialogue();

	//Function that will send the followers of this npc specified by the player in filterenemies to fight the player
	void FollowersAttack(ANPC* follower, APlayer_Char* player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//The destination that the npc is headed towards
	ALocations* targetDestination;

	//Location that the npc was at prior to their move
	ALocations* previousLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Location the npc is at currently, if any
	ALocations* currentLocation;

	//A Location solely used for events
	ALocations* eventLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Waypoint which npc will actually move to
	ALocations* waypoint;

	//Timer used in combat against player to determine if npc should attack
	float attackTimer = 0.0f;

	//Function used in the die state to find a new target
	void FindTarget(ANPC* dyingNPC, ANPC* friendlyFollower, ANPC* enemy, ANPC* enemyFollower);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC Settings")
	//Activity set by location npc is at
	AActivityObject* activity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
	//Array to hold tags, used to determine dialogues and activities
	TArray<FName> personalityTags;

	UFUNCTION(BlueprintImplementableEvent)
	//This function will start the animation on the npc's activity
	void StartActivityEvent();

	UFUNCTION(BlueprintImplementableEvent)
	//This function will end the activity's animation normally
	void EndActivityNormalEvent();

	UFUNCTION(BlueprintImplementableEvent)
	//This function will end the activity's animation with fleeing
	void EndActivityFleeEvent();

	//Function that will serve as individual npc timer for activities, so not everyone changes at once
	bool ActivityTimer();

	//float used for the activity timer
	float activityTime = 0.0f;

	//Max time for the activity timer
	float maxActivityTime = FMath::RandRange(0, 600);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	//Section for tags

	static const FName drunk;
	static const FName dancer;

};
