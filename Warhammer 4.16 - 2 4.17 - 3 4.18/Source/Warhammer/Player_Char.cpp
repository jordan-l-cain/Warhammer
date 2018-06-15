// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "PlayerMovementComponent.h"
#include "Player_Controller.h"
#include "NPC.h"
#include "NPC_Controller.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player_Char.h"


// Sets default values
APlayer_Char::APlayer_Char(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UPlayerMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	
	//Create our components
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	//CameraSpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraSpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	
}

// Called when the game starts or when spawned
void APlayer_Char::BeginPlay()
{
	Super::BeginPlay();

	originalArmRotation = CameraSpringArm->GetComponentRotation();
	originalArmOffset = CameraSpringArm->SocketOffset;
	originalCameraRotation = Camera->RelativeRotation;
	originalSpeed = movementComponent->MaxWalkSpeed;

}

// Called every frame
void APlayer_Char::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayer_Char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayer_Char::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APlayer_Char::ZoomOut);
	InputComponent->BindAction("AttackTop", IE_Pressed, this, &APlayer_Char::AttackTop);
	InputComponent->BindAction("AttackLeft", IE_Pressed, this, &APlayer_Char::AttackLeft);
	InputComponent->BindAction("AttackRight", IE_Pressed, this, &APlayer_Char::AttackRight);
	InputComponent->BindAction("Attack", IE_Pressed, this, &APlayer_Char::Attack);
	InputComponent->BindAction("Block", IE_Pressed, this, &APlayer_Char::Block);
	InputComponent->BindAction("ModeShift", IE_Pressed, this, &APlayer_Char::Shift);
	InputComponent->BindAction("ModeShift", IE_Released, this, &APlayer_Char::UnShift);
	InputComponent->BindAction("Retarget", IE_Pressed, this, &APlayer_Char::Retarget);

	//Hook up every-frame handling for our four axes
	InputComponent->BindAxis("MoveForward", this, &APlayer_Char::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayer_Char::MoveRight);
	InputComponent->BindAxis("LookUp", this, &APlayer_Char::LookUp);
	InputComponent->BindAxis("Turn", this, &APlayer_Char::Turn);
}



void APlayer_Char::MoveForward(float AxisValue)
{
	if (canMove)
	{
		ForwardMovement = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);

		if (ForwardMovement != 0.0f && !ModeShift)
		{
			MovingForward();

			//Scale our movement input axis values by 100 units per second
			ForwardMovement = ForwardMovement * 100.0f;

			AddMovementInput(GetActorForwardVector(), ForwardMovement * GetWorld()->GetDeltaSeconds());
		}
	}
}

void APlayer_Char::MoveRight(float AxisValue)
{
	if (canMove)
	{
		SideMovement = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);

		if (SideMovement != 0.0f && !ModeShift)
		{
			//Scale our movement input axis values by 100 units per second
			SideMovement = SideMovement * 30.0f;
			//TODO make side movement only move actor to right? Not playing feeding direction right, or not moving true right
			playerController->AddYawInput(SideMovement * GetWorld()->GetDeltaSeconds());
			//AddMovementInput(GetActorRightVector(), SideMovement / 10);

			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw + (-1 * SideMovement / 5), 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			//AddMovementInput(Direction, SideMovement / 10);
		}

	}
}

void APlayer_Char::LookUp(float AxisValue)
{
	
	CameraInput.Y = AxisValue * 10 * GetWorld()->GetDeltaSeconds();

	if (RotateArm)
	{
		FRotator NewRotation = Camera->RelativeRotation;
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, 30.0f);

		Camera->SetRelativeRotation(NewRotation);
	} else
	{
		FRotator NewRotation = CameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, 30.0f);
		CameraSpringArm->SetWorldRotation(NewRotation);
	}
	
	// calculate delta for this frame from the rate information

	AddControllerPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayer_Char::Turn(float AxisValue)
{
	//TODO Camera controls where the camera only rotates if nothing is held down, but if the right click is held down, then rotate about the arm
	CameraInput.X = AxisValue * 10 * GetWorld()->GetDeltaSeconds();

	if (RotateArm)
	{
		originalArmRotation.Yaw = player->GetActorRotation().Yaw;

		FRotator CameraRotation = Camera->RelativeRotation;
		CameraRotation.Yaw = FMath::Clamp(CameraRotation.Yaw + CameraInput.X, -40.0f, 40.0f);

		Camera->SetRelativeRotation(CameraRotation);

	} else
	{
		Camera->RelativeRotation.Pitch = -10;
		Camera->RelativeRotation.Yaw = 0;
		CameraSpringArm->SocketOffset = FVector(-20, 50, 200);

		FRotator ArmRotation = CameraSpringArm->RelativeRotation;
		ArmRotation.Yaw += CameraInput.X * 3.0;

		CameraSpringArm->SetRelativeRotation(ArmRotation);
	}
}

void APlayer_Char::AttackTop()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack top called"));
	stance = 0;
}

void APlayer_Char::AttackLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack left called"));
	stance = 1;
}

void APlayer_Char::AttackRight()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack right called"));
	stance = 2;
	//TODO add takeaction bool to these? except would like player to be able to change stances on the fly possibly if we hold the attack button?
}

void APlayer_Char::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack called"));

	if (takeAction)
	{
		inAttackState();

		attacking = true;
		PlayAttackAnimation(0, stance);
	}
}

void APlayer_Char::Block()
{
	UE_LOG(LogTemp, Warning, TEXT("Block called"));

	if (takeAction)
	{
		//TODO Remember to create weapon variable determined by which weapon is equipped
		PlayDefenseAnimation(0, stance);
	}
}

void APlayer_Char::PlayerAttacks(ANPC* enemy)
{
	if (enemy)
	{
		if (strength > enemy->npcHealth)
		{
			//TODO add weapon variable for hit, and later selection for stance
			enemy->CallDeathAnimationEvent(0, 0);
			enemy->npcController->SetState(ENPCStates::DIE);
		} else
		{
			enemy->CallHitAnimationEvent(0, stance);
			enemy->ModHealth(-strength);
		}
	}
}

void APlayer_Char::ZoomIn()
{
	//TODO lerp the zoom value for the arm length to give it a smooth slide
	float zoom = 0;
	zoom += 20;
	zoom = FMath::Clamp<float>(zoom, 0, 50);
	CameraSpringArm->TargetArmLength -= zoom;
}

void APlayer_Char::ZoomOut()
{
	float zoom = 0;
	zoom += 20;
	zoom = FMath::Clamp<float>(zoom, 0, 100);
	CameraSpringArm->TargetArmLength += zoom;
}

void APlayer_Char::Shift()
{
	//UE_LOG(LogTemp, Warning, TEXT("Shift called"));
	//ModeShift = true;
	movementComponent->MaxWalkSpeed = 800;
	Sprint();
}

void APlayer_Char::UnShift()
{
	//UE_LOG(LogTemp, Warning, TEXT("UnShift called"));
	//ModeShift = false;
	movementComponent->MaxWalkSpeed = originalSpeed;
	EndSprint();
}

void APlayer_Char::ResetArm()
{
	Camera->SetRelativeRotation(originalCameraRotation);

	CameraSpringArm->SetWorldRotation(originalArmRotation);
	CameraSpringArm->SocketOffset = originalArmOffset;
}

EPlayerRace APlayer_Char::GetPlayerRace()
{
	return PlayerRace;
}

EPlayerRace APlayer_Char::GetDwarfRace()
{
	return EPlayerRace::Dwarf;
}

EPlayerRace APlayer_Char::GetGreenskinRace()
{
	return EPlayerRace::Greenskin;
}

bool APlayer_Char::GetCanAttack()
{
	return canAttack;
}

void APlayer_Char::ModHealth(float modifier)
{
	playerHealth += modifier;
}

void APlayer_Char::ModCanAttack(bool boolean)
{
	canAttack = boolean;
}

void APlayer_Char::CallMoveStateEvent()
{
	inMoveState();
}

void APlayer_Char::CallAttackAnimationEvent(int weapon, int animation)
{
	PlayAttackAnimation(weapon, animation);
}

void APlayer_Char::CallDefenseAnimationEvent(int weapon, int animation)
{
	PlayDefenseAnimation(weapon, animation);
}

