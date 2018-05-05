// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "Locations.h"
#include "NPC.h"
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

		} else if (libraryActivity)
		{
			location->libraryActivities.Add(this);
			
		} else if (streetActivity)
		{
			location->streetActivities.Add(this);

		} else if (vendorActivity)
		{
			location->vendorActivities.Add(this);

		} else if (customerActivity)
		{
			location->customerActivities.Add(this);

		}
	}
}

// Called every frame
void AActivityObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (activityNPC)
	{
		if (ActivityTimer())
		{
			UE_LOG(LogTemp, Warning, TEXT("Ending activity for %s"), *activityNPC->GetName());
			activityNPC->EndActivityNormalEvent();
			activityNPC = nullptr;
			pauseActionTimer = false;
			time = 0.0f;
			actionTime = 0.0f;
		}
		
		if (actions.Num() > 0 && !pauseActionTimer && ActionTimer())
		{
			PlayAction();
			pauseActionTimer = true;
			actionTime = 0.0f;
		}
	}
}

bool AActivityObject::ActivityTimer()
{
	time += 0.0166f;

	if (time > maxActivityTime)
	{
		UE_LOG(LogTemp, Warning, TEXT("Activity is over for %s"), *activityNPC->GetName());
		return true;
	}

	return false;
}

bool AActivityObject::ActionTimer()
{
	actionTime += 0.0166f;
	///UE_LOG(LogTemp, Warning, TEXT("%f"), actionTime);

	if ((time + 10.0f) > maxActivityTime)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Time is nearing end %s"), *activityNPC->GetName());
	}

	if (actionTime > maxActionTime && (time + 10.0f) < maxActivityTime)
	{
		UE_LOG(LogTemp, Warning, TEXT("Action is called for %s"), *activityNPC->GetName());
		maxActionTime = FMath::RandRange(1, 10);
		return true;
	}

	return false;
}

