// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Locations.generated.h"

class ALocations;
class ANPC;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ELocation : uint8
{
	GRIMNKAIRN UMETA(DisplayName = "Grimn-a-Kairn"),
	GRIMNGON UMETA(DisplayName = "Grimn-Gon"),
	GRIMNGEIRN UMETA(DisplayName = "Grimn-Geirn"),
	GRIMNEN UMETA(DisplayName = "Grimn-EN"),
	GRIMNFELDST UMETA(DisplayName = "Grimn-Feldst"),
	ESTABLISHBIGUNS UMETA(DisplayName = "EstablishmentBiguns"),
	DABOOMPLACE UMETA(DisplayName = "DaBoomPlace"),
	DARUNTIES UMETA(DisplayName = "DaRuntiesDen"),
	DAPLACE UMETA(DisplayName = "DaPlace"),
	DACONTRAPSHINPLACE UMETA(DisplayName = "DaContrapshinPlace"),
	WAYPOINT UMETA(DisplayName = "Waypoint")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EControllingRace : uint8
{
	Dwarf UMETA(DisplayName = "Dwarf"),
	Greenskin UMETA(DisplayName = "Greenskin")
};


USTRUCT(BlueprintType)
struct FLocationsArray
{
	GENERATED_USTRUCT_BODY()
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ALocations*> locations;
};

UCLASS(Blueprintable)
class WARHAMMER_API ALocations : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocations();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Name to describe Location, waypoint means it is used to travel from one location to another, but is not a location
	FText name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Enum for comparison
	ELocation location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Map of arrays which contain directions to each location, The key being the destination, the value being the waypoints to the destination
	TMap< ELocation, FLocationsArray> locationArrays;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Int based on who controls, who is there + how many, used for dwarfs
	int dwarfProbability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Int based on who controls, who is there + how many, used for greenskins
	int greenskinProbability;

	//Function that sort through the locations and choose one based on the race's probability
	static ALocations* GetDestination(ALocations* currentLocation, bool dwarf);

	static void nextWaypoint(ANPC* npc);
	
};
