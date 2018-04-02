// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Locations.h"
#include "ActivityObject.h"


// Sets default values
AActivityObject::AActivityObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActivityObject::BeginPlay()
{
	Super::BeginPlay();
	if (location)
	{
		if (drunkActivity)
		{
			location->drunkActivities.Add(this);

		} else if (dancerActivity)
		{
			location->dancerActivities.Add(this);
		}
	}
}

// Called every frame
void AActivityObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

