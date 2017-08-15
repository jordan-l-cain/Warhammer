// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "PlayerMovementComponent.h"
#include "Player_Controller.h"
#include "Player_Char.h"


// Sets default values
APlayer_Char::APlayer_Char(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UPlayerMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our components
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
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
		MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);

		if (!MovementInput.IsZero())
		{
			MovingForward();
			//Scale our movement input axis values by 100 units per second
			MovementInput.X = MovementInput.GetSafeNormal().X * 100.0f;

			AddMovementInput(GetActorForwardVector(), MovementInput.X * GetWorld()->GetDeltaSeconds());
		}
	}
}

void APlayer_Char::MoveRight(float AxisValue)
{
	if (canMove)
	{
		MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);

		if (!MovementInput.IsZero())
		{
			//Scale our movement input axis values by 100 units per second
			MovementInput.Y = MovementInput.GetSafeNormal().Y * 100.0f;

			playerController->AddYawInput(MovementInput.Y * GetWorld()->GetDeltaSeconds());
		}
	}
}

void APlayer_Char::LookUp(float AxisValue)
{
	CameraInput.Y = AxisValue * 10 * GetWorld()->GetDeltaSeconds();

	if (!RotateArm)
	{
		FRotator NewRotation = Camera->RelativeRotation;
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, 10.0f);
		
		Camera->SetRelativeRotation(NewRotation);
	} else
	{
		FRotator NewRotation = CameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, 10.0f);
		CameraSpringArm->SetWorldRotation(NewRotation);
	}

}

void APlayer_Char::Turn(float AxisValue)
{
	//TODO Camera controls where the camera only rotates if nothing is held down, but if the right click is held down, then rotate about the arm
	CameraInput.X = AxisValue * 10 * GetWorld()->GetDeltaSeconds();
	
	if (!RotateArm)
	{
		originalArmRotation.Yaw = player->GetActorRotation().Yaw;

		FRotator CameraRotation = Camera->RelativeRotation;
		CameraRotation.Yaw = FMath::Clamp(CameraRotation.Yaw + CameraInput.X, -40.0f, 40.0f);

		Camera->SetRelativeRotation(CameraRotation);

	} else
	{
		Camera->RelativeRotation.Pitch = 0;
		Camera->RelativeRotation.Yaw = 0;
		CameraSpringArm->SocketOffset = FVector(0, 0, 0);

		FRotator ArmRotation = CameraSpringArm->RelativeRotation;
		ArmRotation.Yaw += CameraInput.X * 3.0;
		
		CameraSpringArm->SetRelativeRotation(ArmRotation);
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

void APlayer_Char::CallAttackAnimationEvent(int i)
{
	PlayAttackAnimation(i);
}

void APlayer_Char::CallDefenseAnimationEvent(int i)
{
	PlayDefenseAnimation(i);
}