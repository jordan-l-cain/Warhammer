// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "NPC.h"
#include "WarhammerGameModeBase.generated.h"



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

	//Array of all leaders in an event.
	static TArray<ANPC*> dwarfEventList;

	//Array of all leaders in an event.
	static TArray<ANPC*> greenskinEventList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	//Map of the locations, with an enum value that will indicate whether enemies, friendlies or both are present in the location
	TArray< AActor*> Locations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	//TMap of all world conditions that will cause events. Here is the main TMap, from which events will be executed, these bools are set by the TMap in the Dialogue blueprint at the end of conversations
	TMap< FName, bool > WorldConditions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Array of first event locations
	TArray<AActor*> dwarfEventPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Array of first event locations
	TArray<AActor*> greenskinEventPositions;

	//Attack Stat, which determines who is more likely to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	int deadDwarfs;

	//Attack Stat, which determines who is more likely to attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Global Variables")
	int deadGreenskins;

	//Function that will adjust the number of dead npc's depending on the race given, as well as check for events
	void SetDeadNPCs(ENPCRace race, int dead);

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

	UFUNCTION(Category = "Events", BlueprintCallable)
	//This event is called to update world condition bool values, which will also check whether to run events or not
	void SetBools(FName key, bool value);

	//Function that will end the current event
	static void EndEvent(ANPC* caller);

	//An event count int used to compare how many greenskins are at the event as opposed to how many are in the event list
	static int greenskinEventCount;

	//An event count int used to compare how many dwarfs are at the event as opposed to how many are in the event list
	static int dwarfEventCount;

	//Function to remove dead and call start event function
	static void RemoveFromEvent(ANPC* deadNPC);
};
