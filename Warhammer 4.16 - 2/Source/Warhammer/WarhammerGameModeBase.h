// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "WarhammerGameModeBase.generated.h"

class ANPC;

/**
 * 
 */
UCLASS()
class WARHAMMER_API AWarhammerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
public:

	//Array of all leaders in the game.
	static TArray<ANPC*> LeaderList;

	//Attack Stat, which determines who is more likely to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	int deadDwarfs;

	//Attack Stat, which determines who is more likely to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	int deadGreenskins;

	//Function used to find all designated leaders at the start of the game.
	UFUNCTION(BlueprintCallable, Category = "Functions")
	void PopulateLeaderList();

	//Function that replaces a leader with a new leader, called from current leader in death state
	static void ReplaceLeader(int indexOf, ANPC* replacement);
};
