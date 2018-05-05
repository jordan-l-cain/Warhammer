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

	UFUNCTION(BlueprintImplementableEvent)
	//Function in BP, face npc in correct direction for animation
	void FaceActivity();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//The current location of this activity
	ALocations* location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Array of any animations associated with this activity
	TArray<UAnimMontage*> activityAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//One off animations for the activity
	TArray<UAnimMontage*> actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Max time for the activity timer
	float maxActivityTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//NPC pointer to npc currently at this activity 
	ANPC* activityNPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//Bool used to determine if an npc is already at this activity
	bool occupied = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool drunkActivity = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool libraryActivity = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool vendorActivity = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool customerActivity = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool streetActivity = false;

	float time = 0.0f;
	float actionTime = 0.0f;
	float maxActionTime = FMath::RandRange(4, 15);

	//Will send npc to next activity
	bool ActivityTimer();

	//Function that will play one off animations on npc at activity
	bool ActionTimer();

	UFUNCTION(BlueprintImplementableEvent)
	//Will return false once the angle between the npc and the activity is between 1 and -1
	bool GetAngleFromActivity(ANPC* npc);

	UFUNCTION(BlueprintImplementableEvent)
	//Function that will play an animation pertaining to this activity
	void PlayAction();

	UPROPERTY(BlueprintReadWrite)
	//bool that will stop timer from activating before animation is finished
	bool pauseActionTimer = false;
};


