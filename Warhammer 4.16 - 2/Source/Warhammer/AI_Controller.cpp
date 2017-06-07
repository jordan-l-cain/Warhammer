// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "AI_Controller.h"

// Sets default values
AAI_Controller::AAI_Controller()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAI_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (character)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the character"), *character->GetName())
	}
	
}

// Called every frame
void AAI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	///overlapping actors array passed by the ai
	//GetOverlappingActors(OverlappingActors);

	//Movement.MoveAI(GetControllerAI(), OverlappingActors);
	MoveAI(character, OverlappingActors);
	

}

// Called to bind functionality to input
void AAI_Controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

ECharacterType AAI_Controller::GetCharacterType()
{
	return characterType;
}

///ControlRotation accessed via GetControlRotation() will be used to control rotation


