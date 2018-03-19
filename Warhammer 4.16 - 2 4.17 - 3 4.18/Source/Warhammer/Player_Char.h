// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_Char.generated.h"

class APlayer_Controller;
class UPlayerMovementComponent;
class ANPC;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPlayerRace : uint8
{
	Dwarf UMETA(DisplayName = "Dwarf"),
	Greenskin UMETA(DisplayName = "Greenskin")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPlayerDwarfType : uint8
{
	SLAYER UMETA(DisplayName = "Slayer"),
	IRONBREAKER UMETA(DisplayName = "Iron Breaker")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPlayerGreenskinType : uint8
{
	CHOPPA UMETA(DisplayName = "Choppa"),
	BIGUN UMETA(DisplayName = "Bigun")
};

UCLASS()
class WARHAMMER_API APlayer_Char : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Char(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate = 30;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SideMovement;

	//Public variable, used by npcs to determine movement direction
	float ForwardMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	//Used to move camera, as well as in blueprint to check if to lock the player camera to a target or not
	UPROPERTY(BlueprintReadOnly)
	FVector2D CameraInput;

	//Variable used to reset player back to original maxWalkSpeed
	float originalSpeed;

	//Player Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	FText Name;

	//Player Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	float playerHealth;

	//Strength Stat, which determines amount of damage done to enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	float strength;

	//Attack Stat, which determines who is more likely to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	float attack;

	//Defense Stat, which determines blocking/dodging capability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	float defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	//Player's attack and defense stance
	int stance = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	// Instance of the player
	APlayer_Char* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	// Instance of the player's controller.
	APlayer_Controller* playerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	// Instance of the player's movement component.
	UPlayerMovementComponent* movementComponent;
	
	UPROPERTY(EditAnywhere, Category = "Player Settings")
	// Race of the player
	EPlayerRace PlayerRace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	EPlayerDwarfType DwarfType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	EPlayerGreenskinType GreenskinType;

	UPROPERTY(VisibleAnywhere, Category = "Player Settings")
	//Array of player's npc followers
	TArray<ANPC*> followers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	//Boolean used to determine whether the Spring Arm or camera are rotating.
	bool RotateArm = false;

	UFUNCTION(Category = "Movement Events", BlueprintImplementableEvent)
	//Event that is called when the player is moving, which plays the animation through blueprint
	void MovingForward();

	UFUNCTION(Category = "Movement Events", BlueprintCallable)
	//Event that is called when the player is moving, which plays the animation through blueprint
	void ResetArm();

	//Boolean that determines who can attack, read/set by combat class 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Settings")
	bool canAttack = false;

	//Boolean that determines who can attack, read/set by combat class 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Settings")
	bool attacking = false;

	//Boolean used to determine if this npc is dead.
	bool isDead = false;

	//Boolean that keeps the player from moving during combat animations
	bool canMove = true;
	
	//Boolean used to stop the player from taking action
	UPROPERTY(BlueprintReadWrite)
	bool takeAction = true;

	//Boolean set in PlayerBlock_AnimState, read by NPC_Controller_BP Player Blocks function
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Settings")
	bool playerBlocking = false;

	//Boolean set in PlayerBlock_AnimState, read by NPC_Controller_BP Player Blocks function
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Settings")
	bool playerParrying = false;

	//Pointer to npc the player is fighting
	ANPC* npcTarget = nullptr;

	UFUNCTION(Category = "Functions", BlueprintCallable)
	// Return function that will allow the movement script to determine the npc type
	EPlayerRace GetPlayerRace();

	UFUNCTION(Category = "Functions", BlueprintCallable)
	// Returns ENPCRace of Dwarf for comparison
	EPlayerRace GetDwarfRace();

	UFUNCTION(Category = "Functions", BlueprintCallable)
	// Returns ENPCRace of Dwarf for comparison
	EPlayerRace GetGreenskinRace();

	//Read function for canAttack boolean
	bool GetCanAttack();

	//Function that adjusts npc health
	void ModHealth(float modifier);

	//Set function for canAttack boolean
	void ModCanAttack(bool boolean);

	//This function is used to call the Attack Animation event since it can only be called from this class.
	void CallMoveStateEvent();

	UFUNCTION(Category = "States", BlueprintImplementableEvent)
	//Determines when the Anim blueprint can play the movement animations. Called in NPC_Controller_BP
	void inMoveState();

	UFUNCTION(Category = "States", BlueprintImplementableEvent)
	void inAttackState();

	//This function is used to call the Attack Animation event since it can only be called from this class.
	void CallAttackAnimationEvent(int weapon, int animation);

	//This function is used to call the Attack Animation event since it can only be called from this class.
	void CallDefenseAnimationEvent(int weapon, int animation);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayAttackAnimation(int weapon, int animation);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayDefenseAnimation(int weapon, int animation);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function will lock the player's camera onto a given target
	void LockOnTarget(AActor* target);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//Called by player, sends raycast and makes colliding npc the target
	void Retarget();

	UFUNCTION(Category = "Functions", BlueprintCallable)
	//Called by PlayerAttacks_AnimState, checks for killing blow or not, damages health
	void PlayerAttacks(ANPC* enemy);


private:

	float ZoomFactor;
	bool bZoomingIn;
	bool ModeShift = false;
	FRotator originalCameraRotation;
	FRotator originalArmRotation;
	FVector originalArmOffset;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void Turn(float AxisValue);
	void AttackTop();
	void AttackLeft();
	void AttackRight();
	void Attack();
	void Block();
	void ZoomIn();
	void ZoomOut();

	void Shift();
	void UnShift();
};
