// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPCMovementComponent.h"
#include "NPC_Controller.h"
#include "Player_Char.h"
#include "PlayerMovementComponent.h"
#include "Locations.h"
#include "NPC.h"

const FName ANPC::drink = FName(TEXT("Drink"));
const FName ANPC::library = FName(TEXT("Library"));
const FName ANPC::street = FName(TEXT("Street"));
const FName ANPC::vendor = FName(TEXT("Vendor"));
const FName ANPC::customer = FName(TEXT("Customer"));

// Sets default values
ANPC::ANPC(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UNPCMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	if (npcRace == ENPCRace::Dwarf)
	{
		dwarf = true;

		if (GetNPCType() == GetChampionType())
		{
			for (TActorIterator<ANPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ANPC *actor = *ActorItr;

				if ((actor->GetNPCRace() == ANPC::GetDwarfRace()) && (actor->GetNPCType() == actor->GetCommonType()))
				{
					if (!followers.Contains(actor) && followers.Num() < 42 && !actor->leader)
					{
						///UE_LOG(LogTemp, Warning, TEXT("%s: Adding %s to my array."), *npc->GetName(), *actor->GetName());
						actor->leader = npc;
						followers.Add(actor);
						actor->movementComponent->followerIndex = followers.Find(actor);
					}
				}
			}
		}
	}

	if (npcRace == ENPCRace::Greenskin)
	{
		greenskin = true;

		if (GetNPCType() == GetChampionType())
		{
			for (TActorIterator<ANPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ANPC *actor = *ActorItr;

				if ((actor->GetNPCRace() == ANPC::GetGreenskinRace()) && (actor->GetNPCType() == actor->GetCommonType()))
				{
					if (!followers.Contains(actor) && followers.Num() < 41 && !actor->leader)
					{
						UE_LOG(LogTemp, Warning, TEXT("%s: Adding %s to my array."), *npc->GetName(), *actor->GetName());
						actor->leader = npc;
						followers.Add(actor);
						actor->movementComponent->followerIndex = followers.Find(actor);
					}
				}
			}
		}
	}
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::SetTick(bool toTick)
{
	SetActorTickEnabled(toTick);
	npcController->SetActorTickEnabled(toTick);
	UE_LOG(LogTemp, Warning, TEXT("Should be disabled"));
}

ENPCRace ANPC::GetNPCRace()
{
	return npcRace;
}

ENPCRace ANPC::GetDwarfRace()
{
	return ENPCRace::Dwarf;
}

ENPCRace ANPC::GetGreenskinRace()
{
	return ENPCRace::Greenskin;
}

ENPCRace ANPC::GetEnemyRace()
{
	return ENPCRace::Enemy;
}

ENPCType ANPC::GetNPCType()
{
	return npcType;
}

ENPCType ANPC::GetChampionType()
{
	return ENPCType::CHAMPION;
}

ENPCType ANPC::GetCommonType()
{
	return ENPCType::COMMON;
}

ENPCType ANPC::GetCommonerType()
{
	return ENPCType::COMMONER;
}

void ANPC::ModHealth(float modifier)
{
	if (npcHealth > 0)
	{
		npcHealth += modifier;
		///UE_LOG(LogTemp, Warning, TEXT("%s's health is %f"), *npc->GetName(), npcHealth);
	}

	if (npcHealth <= 0)
	{
		npcHealth = 0;
	}
}

void ANPC::CallMoveStateEvent()
{
	inMoveState();
}

void ANPC::CallAttackAnimationEvent(int weapon, int animation)
{
	PlayAttackAnimation(weapon, animation);
}

void ANPC::CallBlockedAnimationEvent(int weapon, int animation)
{
	PlayBlockedAnimation(weapon, animation);
}

void ANPC::CallDefenseAnimationEvent(int weapon, int animation)
{
	PlayDefenseAnimation(weapon, animation);
}

void ANPC::CallHitAnimationEvent(int weapon, int animation)
{
	PlayHitAnimation(weapon, animation);
}

void ANPC::CallDeathAnimationEvent(int weapon, int animation)
{
	PlayDeathAnimation(weapon, animation);
}

void ANPC::EndDialogue()
{
	npc->movementComponent->moveToLocation = true;
	npc->npcController->SetState(ENPCStates::IDLE);
	UE_LOG(LogTemp, Warning, TEXT("Resetting npc"));
}

void ANPC::FollowersAttack(ANPC* follower, APlayer_Char* player)
{
	//TODO every follower after this follower -1 on follower index
	UE_LOG(LogTemp, Warning, TEXT("Follower called by player is %s"), *follower->GetName());
	if (followers.Contains(follower))
	{
		if (!npc->movementComponent->enemyLeader)
		{
			follower->movementComponent->playerTarget = player;
			float slice = 2 * 3.14 / followers.Num();
			int i = 0;

			FVector center = player->GetActorLocation();


			for (auto* fol : followers)
			{
				if (fol->npcController->curState != ENPCStates::ATTACKPLAYER && !fol->movementComponent->playerTarget)
				{
					float radius = FMath::RandRange(800, 1400);
					float angle = slice * i;
					FVector CircleLocation;
					CircleLocation.X = radius * FMath::Cos(angle) + center.X + FMath::RandRange(0, 400);
					CircleLocation.Y = radius * FMath::Sin(angle) + center.Y + FMath::RandRange(0, 400);

					fol->npcController->MoveToLocation(CircleLocation);
					fol->npcController->SetState(ENPCStates::ATTACKPLAYER);
					i++;

				} else if (fol->movementComponent->playerTarget)
				{
					fol->npcController->MoveToActor(player);
					fol->npcController->SetState(ENPCStates::ATTACKPLAYER);
				}
			}

			if (npc->npcController->curState != ENPCStates::ATTACKPLAYER)
			{
				//npc->movementComponent->playerTarget = player;
				//npc->npcController->MoveToActor(player);
				//npc->npcController->SetState(ENPCStates::ATTACKPLAYER);
			}

			if (!player->movementComponent->enemyTarget)
			{
				player->movementComponent->enemyTarget = follower;
				player->LockOnTarget(player->movementComponent->enemyTarget);
				
				//TODO remember to re add if they kill player
				followers.Remove(follower);

				for (auto* fellowFollower : followers)
				{
					fellowFollower->movementComponent->followerIndex = followers.Find(fellowFollower);
				}
			}
		} else
		{
			if (follower->movementComponent->followTarget)
			{
				if (follower->movementComponent->battleFollower)
				{
					follower->movementComponent->followTarget->movementComponent->battleFollower = follower->movementComponent->battleFollower;
					follower->movementComponent->battleFollower->movementComponent->followTarget = follower->movementComponent->followTarget;

				} else
				{
					follower->movementComponent->followTarget->movementComponent->battleFollower = nullptr;
				}
			}

			follower->movementComponent->playerTarget = player;
			follower->npcController->MoveToActor(player);
			follower->npcController->SetState(ENPCStates::ATTACKPLAYER);

		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Follower %s not in followers"), *follower->GetName());

	}
}


void ANPC::FindTarget(ANPC * dyingNPC, ANPC * friendlyFollower, ANPC * enemy, ANPC * enemyFollower)
{
	//TODO disallow enemies with a player target
	int i = dyingNPC->leader->followers.Find(dyingNPC);

	//TODO fix when an enemy can't get a target but their follower can
	if (friendlyFollower)
	{
		if (!friendlyFollower->movementComponent->enemyTarget && !friendlyFollower->movementComponent->playerTarget)
		{
			///UE_LOG(LogTemp, Warning, TEXT("%s has a battlefollower for %s"), *dyingNPC->GetName(), *enemy->GetName());
			//if this dying npc has a battle follower, set the battle follower as the enemy's target and vice versa
			friendlyFollower->movementComponent->enemyTarget = enemy;
			enemy->movementComponent->enemyTarget = friendlyFollower;
			enemy->movementComponent->move = true;
			friendlyFollower->movementComponent->followTarget = nullptr;

		} else
		{
			//TODO find a target for the enemy since the friendly follower had a target, possibly add a function to check followers to see who doesn't have an enemy if the below doesn't work
			i = dyingNPC->leader->followers.Find(friendlyFollower);

			if (i - 1 > 1)
			{
				//Check if the -1 has an enemy target
				if (!dyingNPC->leader->followers[i - 1]->movementComponent->enemyTarget && !enemy->movementComponent->enemyTarget && !enemy->movementComponent->playerTarget)
				{
					enemy->movementComponent->enemyTarget = dyingNPC->leader->followers[i - 1];
					dyingNPC->leader->followers[i - 1]->movementComponent->enemyTarget = enemy;
					enemy->movementComponent->move = true;

					//Else if check if the -1 has a battlefollower, and if the battlefollower has an enemy target
				} else if (dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower && !dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->enemyTarget && !dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->playerTarget && !enemy->movementComponent->enemyTarget && !enemy->movementComponent->playerTarget)
				{
					enemy->movementComponent->enemyTarget = dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower;
					dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->enemyTarget = enemy;
					enemy->movementComponent->move = true;

				}
				//Check if the dyingNPC's leader's followers at +1 exists
			} else if (i + 1 < dyingNPC->leader->followers.Num())
			{
				//Check if the -1 has an enemy target
				if (!dyingNPC->leader->followers[i + 1]->movementComponent->enemyTarget && !enemy->movementComponent->enemyTarget)
				{
					enemy->movementComponent->enemyTarget = dyingNPC->leader->followers[i + 1];
					dyingNPC->leader->followers[i + 1]->movementComponent->enemyTarget = enemy;
					enemy->movementComponent->move = true;

					//Else if check if the -1 has a battlefollower, and if the battlefollower has an enemy target
				} else if (dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower && !dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->enemyTarget && !dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->playerTarget && !enemy->movementComponent->enemyTarget && !enemy->movementComponent->playerTarget)
				{
					enemy->movementComponent->enemyTarget = dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower;
					dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->enemyTarget = enemy;
					enemy->movementComponent->move = true;

				}
			}
		}

		//if the enemy has a follower and that follower does not have an enemy target
		if (enemyFollower && !enemyFollower->movementComponent->enemyTarget)
		{
			//Check if the npc's leader's followers at +1 exists
			if (i + 1 < dyingNPC->leader->followers.Num())
			{
				//Then check if the +1 has an enemy target
				if (!dyingNPC->leader->followers[i + 1]->movementComponent->enemyTarget && !dyingNPC->leader->followers[i + 1]->movementComponent->playerTarget && !enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->playerTarget)
				{
					///UE_LOG(LogTemp, Warning, TEXT("Setting the enemy target of %s's battle follower to +1 of leader's followers, %s"), *enemyFollower->GetName(), *dyingNPC->leader->followers[i + 1]->GetName());
					dyingNPC->leader->followers[i + 1]->movementComponent->enemyTarget = enemyFollower;
					enemyFollower->movementComponent->enemyTarget = dyingNPC->leader->followers[i + 1];

					//Else check if the +1 has a battlefollower and they don't have an enemy target
				} else if (dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower && !dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->enemyTarget && !dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->playerTarget && !enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->playerTarget)
				{
					///UE_LOG(LogTemp, Warning, TEXT("Setting the enemy target of %s's battle follower to the battle follower of the +1 leader's follower, %s"), *enemyFollower->GetName(), *dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->GetName());
					dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->enemyTarget = enemyFollower;
					enemyFollower->movementComponent->enemyTarget = dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower;

				}
			//Check if the dyingNPC's leader's followers at -1 exists
			} else if (i - 1 > 0)
			{
				//Then check if the -1 has an enemy target
				if (!dyingNPC->leader->followers[i - 1]->movementComponent->enemyTarget && !dyingNPC->leader->followers[i - 1]->movementComponent->playerTarget && !enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->playerTarget)
				{
					///UE_LOG(LogTemp, Warning, TEXT("Setting the enemy target of %s's battle follower to -1 of leader's followers, %s"), *enemyFollower->GetName(), *dyingNPC->leader->followers[i - 1]->GetName());
					dyingNPC->leader->followers[i - 1]->movementComponent->enemyTarget = enemyFollower;
					enemyFollower->movementComponent->enemyTarget = dyingNPC->leader->followers[i - 1];

				//Else check if the -1 has a battlefollower
				} else if (dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower && !dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->enemyTarget && !dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->playerTarget && !enemyFollower->movementComponent->enemyTarget)
				{
					///UE_LOG(LogTemp, Warning, TEXT("Setting the enemy target of %s's battle follower to the battle follower of the -1 leader's follower, %s"), *enemyFollower->GetName(), *dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->GetName());
					dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->enemyTarget = enemyFollower;
					enemyFollower->movementComponent->enemyTarget = dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower;
				}
			}

			/*
			//If the enemy's battlefollower now has an enemytarget and has a battlefollower
			if (enemyFollower->movementComponent->enemyTarget && enemyFollower->movementComponent->battleFollower)
			{
			//Set the enemy's battlefollower to the former battlefollower's battlefollower
			ANPC* oldFollower = enemyFollower;
			ANPC* newFollower = enemyFollower->movementComponent->battleFollower;

			newFollower->movementComponent->followTarget = enemy;
			enemyFollower = newFollower;
			oldFollower->movementComponent->battleFollower = nullptr;

			} else if(enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->battleFollower)
			{
			enemyFollower = nullptr;
			}*/
		}

	//Else if the dyingNPC doesn't have a battle follower
	} else if (!friendlyFollower)
	{
		///UE_LOG(LogTemp, Warning, TEXT("%s does not have a battlefollower for %s"), *dyingNPC->GetName(), *enemy->GetName());
		//Check if the dyingNPC's leader's followers at -1 exists
		if (i - 1 > 1)
		{
			//Check if the -1 has an enemy target
			if (!dyingNPC->leader->followers[i - 1]->movementComponent->enemyTarget && !dyingNPC->leader->followers[i - 1]->movementComponent->playerTarget && !enemy->movementComponent->enemyTarget && !enemy->movementComponent->playerTarget)
			{
				enemy->movementComponent->enemyTarget = dyingNPC->leader->followers[i - 1];
				dyingNPC->leader->followers[i - 1]->movementComponent->enemyTarget = enemy;
				enemy->movementComponent->move = true;

			//Else if check if the -1 has a battlefollower, and if the battlefollower has an enemy target
			} else if (dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower && !dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->enemyTarget && !dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->playerTarget && !enemy->movementComponent->enemyTarget && !enemy->movementComponent->playerTarget)
			{
				enemy->movementComponent->enemyTarget = dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower;
				dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->enemyTarget = enemy;
				enemy->movementComponent->move = true;

			}
		//Check if the dyingNPC's leader's followers at +1 exists
		} else if (i + 1 < dyingNPC->leader->followers.Num())
		{
			//Check if the -1 has an enemy target
			if (!dyingNPC->leader->followers[i + 1]->movementComponent->enemyTarget && !dyingNPC->leader->followers[i + 1]->movementComponent->playerTarget && !enemy->movementComponent->enemyTarget && !enemy->movementComponent->playerTarget)
			{
				enemy->movementComponent->enemyTarget = dyingNPC->leader->followers[i + 1];
				dyingNPC->leader->followers[i + 1]->movementComponent->enemyTarget = enemy;
				enemy->movementComponent->move = true;

				//Else if check if the -1 has a battlefollower, and if the battlefollower has an enemy target
			} else if (dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower && !dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->enemyTarget && !dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->playerTarget && !enemy->movementComponent->enemyTarget && !enemy->movementComponent->playerTarget)
			{
				enemy->movementComponent->enemyTarget = dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower;
				dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->enemyTarget = enemy;
				enemy->movementComponent->move = true;

			}
		}

		//if the enemy has a follower and that follower does not have an enemy target
		if (enemyFollower && !enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->playerTarget)
		{
			//Check if the dyingNPC's leader's followers at +1 exists
			if (i + 1 < dyingNPC->leader->followers.Num())
			{
				//Then check if the +1 has an enemy target
				if (!dyingNPC->leader->followers[i + 1]->movementComponent->enemyTarget && !dyingNPC->leader->followers[i + 1]->movementComponent->playerTarget && !enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->enemyTarget)
				{
					///UE_LOG(LogTemp, Warning, TEXT("Setting the enemy target of %s's battle follower to +1 of leader's followers, %s"), *enemyFollower->GetName(), *dyingNPC->leader->followers[i + 1]->GetName());
					dyingNPC->leader->followers[i + 1]->movementComponent->enemyTarget = enemyFollower;
					enemyFollower->movementComponent->enemyTarget = dyingNPC->leader->followers[i + 1];

				//Else check if the +1 has a battlefollower and they don't have an enemy target
				} else if (dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower && !dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->enemyTarget && !dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->playerTarget && !enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->enemyTarget)
				{
					///UE_LOG(LogTemp, Warning, TEXT("Setting the enemy target of %s's battle follower to the battle follower of the +1 leader's follower, %s"), *enemyFollower->GetName(), *dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->GetName());
					dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower->movementComponent->enemyTarget = enemyFollower;
					enemyFollower->movementComponent->enemyTarget = dyingNPC->leader->followers[i + 1]->movementComponent->battleFollower;

				}
			//Check if the dyingNPC's leader's followers at -1 exists
			} else if (i - 1 > 0)
			{
				//Then check if the -1 has an enemy target
				if (!dyingNPC->leader->followers[i - 1]->movementComponent->enemyTarget && !dyingNPC->leader->followers[i - 1]->movementComponent->playerTarget && !enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->enemyTarget)
				{
					///UE_LOG(LogTemp, Warning, TEXT("Setting the enemy target of %s's battle follower to -1 of leader's followers, %s"), *enemyFollower->GetName(), *dyingNPC->leader->followers[i - 1]->GetName());
					dyingNPC->leader->followers[i - 1]->movementComponent->enemyTarget = enemyFollower;
					enemyFollower->movementComponent->enemyTarget = dyingNPC->leader->followers[i - 1];

				//Else check if the -1 has a battlefollower
				} else if (dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower && !dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->enemyTarget && !dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->playerTarget && !enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->enemyTarget)
				{
					///UE_LOG(LogTemp, Warning, TEXT("Setting the enemy target of %s's battle follower to the battle follower of the -1 leader's follower, %s"), *enemyFollower->GetName(), *dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->GetName());
					dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower->movementComponent->enemyTarget = enemyFollower;
					enemyFollower->movementComponent->enemyTarget = dyingNPC->leader->followers[i - 1]->movementComponent->battleFollower;
				}
			}
			/*
			//If the enemy's battlefollower now has an enemytarget and has a battlefollower
			if (enemyFollower->movementComponent->enemyTarget && enemyFollower->movementComponent->battleFollower)
			{
			//Set the enemy's battlefollower to the former battlefollower's battlefollower
			ANPC* oldFollower = enemyFollower;
			ANPC* newFollower = enemyFollower->movementComponent->battleFollower;

			newFollower->movementComponent->followTarget = enemy;
			enemyFollower = newFollower;
			oldFollower->movementComponent->battleFollower = nullptr;

			} else if (enemyFollower->movementComponent->enemyTarget && !enemyFollower->movementComponent->battleFollower)
			{
			enemyFollower = nullptr;
			}*/
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("There are no battle follower's nor followers to the left or right or battlefollowers of the followers for %s"), *enemy->GetName());
		
		if (npc->leader)
		{
			enemy->movementComponent->enemyTarget = npc->leader;
		}
	}
	/* else if (dyingNPC->leader && !enemy->isLeader)
	{
	//is this dyingNPC has a leader, and they don't have a follower and they are not a leader
	if (!dyingNPC->leader->movementComponent->enemyTarget)
	{
	//Then if the leader doesn't have a target, make it's target this dyingNPC's enemy, and vice versa
	enemy->movementComponent->move = true;
	enemy->movementComponent->enemyTarget = dyingNPC->leader;
	dyingNPC->leader->movementComponent->enemyTarget = enemy;
	} else
	{
	//however if the leader does have a target, only make the enemy's target the leader, so they'll move to but not attack
	enemy->movementComponent->move = true;
	enemy->movementComponent->enemyTarget = dyingNPC->leader;
	}
	} else
	{
	//and if this dyingNPC didn't have a follower, nor does it have a leader, and is a leader
	enemy->movementComponent->move = true;
	enemy->movementComponent->enemyTarget = nullptr;
	}*/
}

void ANPC::NextActivity(ANPC* activityNPC)
{
	activityNPC->currentLocation->GetActivity(activityNPC);
	activityNPC->movementComponent->atActivity = false;
	activityNPC->inActivity = false;
	UE_LOG(LogTemp, Warning, TEXT("Next activity for %s"), *activityNPC->GetName());
}

bool ANPC::ActivityTimer(float maxTime)
{
	activityTime += 0.01f;

	if (activityTime > maxTime)
	{
		return true;
	}

	return false;
}

