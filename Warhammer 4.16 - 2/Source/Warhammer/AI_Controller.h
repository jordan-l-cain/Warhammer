// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Movement.h"
#include "GameFramework/Controller.h"
#include "AI_Controller.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ECharacterType : uint8
{
	Dwarf UMETA(DisplayName = "Dwarf"),
	Greenskin UMETA(DisplayName = "Greenskin"),
	Enemy	UMETA(DisplayName = "Enemy")
};

/**
 * This script will control the AI's states and actions.
 */
UCLASS()
class WARHAMMER_API AAI_Controller : public AMovement
{
	GENERATED_BODY()
	
public:

	// Sets default values for this pawn's properties
	AAI_Controller();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Settings")
	//Enum used to set a character type that is readable by the movement script, so it may determine it's actions
	ECharacterType characterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Settings")
	AActor* character;

	//Array used to store all nearby actors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Settings")
	TArray<AActor*> OverlappingActors;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Return function that will allow the movement script to determine the character type
	ECharacterType GetCharacterType();

private:

	
	
};
