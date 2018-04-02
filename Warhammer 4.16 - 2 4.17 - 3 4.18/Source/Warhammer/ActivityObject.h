// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivityObject.generated.h"

class ANPC;
class ALocations;

UCLASS(Blueprintable)
class WARHAMMER_API AActivityObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivityObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//The current location of this activity
	ALocations* location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Array of any animations associated with this activity
	TArray<UAnimMontage*> activityAnimations;

	//NPC pointer to npc currently at this activity 
	ANPC* npc;

	//Bool used to determine if an npc is already at this activity
	bool occupied = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool drunkActivity = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool dancerActivity = false;
};
