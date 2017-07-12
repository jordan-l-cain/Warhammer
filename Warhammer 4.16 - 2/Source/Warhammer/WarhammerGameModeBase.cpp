// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "WarhammerGameModeBase.h"

///int AWarhammerGameModeBase::deadDwarfs;
///int AWarhammerGameModeBase::deadGreenskins;

void AWarhammerGameModeBase::PrintKills(int a, int b)
{
	UE_LOG(LogTemp, Warning, TEXT("Number of dead dwarfs: %f."), a);
	UE_LOG(LogTemp, Warning, TEXT("Number of dead greenskins: %f."), b)
}
