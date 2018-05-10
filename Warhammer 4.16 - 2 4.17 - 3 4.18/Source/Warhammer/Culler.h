// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Culler.generated.h"

UCLASS()
class WARHAMMER_API ACuller : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACuller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Actors to cull
	TArray<AActor*> culledActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//For when culled actors are on outside of actor
	float interiorDistance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Distance used for regular culling; IE: player is far away from culler
	float exteriorDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Boolean used to determine if culler should hide the actors as well as stop tick
	bool hide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//Used so the culler isn't firing off every frame.
	float delayTimer;

};
