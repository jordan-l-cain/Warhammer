// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldEvents.generated.h"

class ANPC;


UCLASS(Blueprintable)
class WARHAMMER_API AWorldEvents : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldEvents();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static AWorldEvents* worldEventBP;

	//First Event Function
	static void FirstEvent(TArray<ANPC*> Leaders, TArray<AActor*> dwarfPositions, TArray<AActor*> greenskinPositions);
	
	/*
		TODO create a state that takes a function as a parameter in the player controller, so that things like locations can call different
		events and the npc will run through that event, rather than listing all the events in that state
		Each location should have a leader of that location, and once an npc gets to that location, the location leader becomes the npc's leader in case of battle
	*/
	
};
