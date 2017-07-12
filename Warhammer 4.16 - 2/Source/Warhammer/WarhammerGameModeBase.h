// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "WarhammerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WARHAMMER_API AWarhammerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
public:

	//Attack Stat, which determines who is more likely to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	int deadDwarfs;

	//Attack Stat, which determines who is more likely to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	int deadGreenskins;

	static void PrintKills(int a, int b);
};
