// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "WarhammerGameModeBase.generated.h"

class ANPC;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ELocationStats : uint8
{
	NONE UMETA(DisplayName = "None"),
	ENEMIES UMETA(DisplayName = "Enemies"),
	FRIENDLIES UMETA(DisplayName = "Friendlies"),
	ENEMIESFRIENDS UMETA(DisplayName = "EnemiesFriends")
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	//Map of the locations, with an enum value that will indicate whether enemies, friendlies or both are present in the location
	TArray< AActor*> Locations;

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
	static void ReplaceLeader(int indexOf, ANPC* replacement, ANPC* oldLeader);

	//Function that leaders will call to find a location to move to
	UFUNCTION( BlueprintCallable, Category = "Functions")
	void SetTravelLocation(const ANPC* caller);

	UFUNCTION(BlueprintImplementableEvent, Category = "Functions")
	void SetTravelLocationEvent(const ANPC* caller);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	//Int used to set the probability of traveling to a location
	int odds;
};
