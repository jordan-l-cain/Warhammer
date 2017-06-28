// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_Controller.generated.h"

class ANPC;
class UNPCMovementComponent;

enum class ENPCStates : uint8
{
	IDLE UMETA(DisplayName = "Idle"),
	MOVE UMETA(DisplayName = "Move"),
	ATTACK UMETA(DisplayName = "Attack"),
	DIE UMETA(DisplayName = "Die")
};

/**
 * This class will handle all run-time NPC States and calling of Actions, delegated out to their respective classes
 */
UCLASS(Blueprintable)
class WARHAMMER_API ANPC_Controller : public AAIController
{
	GENERATED_BODY()
	
public:

	// Sets default values for this pawn's properties
	ANPC_Controller();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//ANPC class instance
	ANPC* npc;

protected:
	
	UFUNCTION(BlueprintCallable, Category= "Functions")
	void Play();


	//Current state the AI is in
	ENPCStates curState;

public:

	UFUNCTION(BlueprintCallable, Category = "Functions")
	// Called every frame
	void Tick(float DeltaTime);

private:

	//Function that sets the AI's state
	void SetState(ENPCStates state);

	void StateIdle();

	void StateMove();

	void StateAttack();

	void StateDie();

};

