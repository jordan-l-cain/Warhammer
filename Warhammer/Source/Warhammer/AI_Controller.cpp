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

	UE_LOG(LogTemp, Warning, TEXT("%s is the AI."), *GetControlledAI()->GetName());

}

// Called every frame
void AAI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Movement.MoveAI(GetControllerAI(), OverlappingActors);
	MoveAI(GetControlledAI(), OverlappingActors);
	

}

// Called to bind functionality to input
void AAI_Controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

///ControlRotation accessed via GetControlRotation() will be used to control rotation
APawn* AAI_Controller::GetControlledAI() const
{
	return Controller->GetPawn();

}

