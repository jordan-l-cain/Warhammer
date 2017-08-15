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

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	UPROPERTY(VisibleAnywhere, Category = "Player Settings")
	// Which combat class the Dwarf player is.
	EPlayerDwarfType DwarfType;

	UPROPERTY(VisibleAnywhere, Category = "Player Settings")
	// Which combat class the Greenskin Player is.
	EPlayerGreenskinType GreenskinType;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	bool canAttack = false;

	//Boolean that determines who can attack, read/set by combat class 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Settings")
	bool attacking = false;

	//Boolean used to determine if this npc is dead.
	bool isDead = false;

	//Boolean that keeps the player from moving during combat animations
	bool canMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
	//This array is used to store and access all attack animations
	TArray<UAnimMontage*> attackAnims;

	//Pointer to npc the player is fighting
	ANPC* npcTarget = nullptr;


public:
	//All getter/setter functions

	// Return function that will allow the movement script to determine the npc type
	EPlayerRace GetPlayerRace();

	// Returns ENPCRace of Dwarf for comparison
	EPlayerRace GetDwarfRace();

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
	void CallAttackAnimationEvent(int i);

	//This function is used to call the Attack Animation event since it can only be called from this class.
	void CallDefenseAnimationEvent(int i);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayAttackAnimation(int i);

	UFUNCTION(Category = "Functions", BlueprintImplementableEvent)
	//This function sends which animation index to play as a parameter
	void PlayDefenseAnimation(int i);

private:

	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;
	FRotator originalCameraRotation;
	FRotator originalArmRotation;
	FVector originalArmOffset;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void Turn(float AxisValue);
	void ZoomIn();
	void ZoomOut();
};
