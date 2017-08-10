// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player_Controller.generated.h"


enum class EPlayerStates : uint8
{
	IDLE UMETA(DisplayName = "Idle"),
	MOVE UMETA(DisplayName = "Move"),
	ATTACK UMETA(DisplayName = "Attack"),
	DIE UMETA(DisplayName = "Die")
};

/**
 * 
 */
UCLASS()
class WARHAMMER_API APlayer_Controller : public APlayerController
{
	GENERATED_BODY()
	
	
	
	
};
