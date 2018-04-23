// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPCMovementComponent.h"
#include "Combat.h"
#include "WarhammerGameModeBase.h"
#include "Locations.h"
#include "Player_Char.h"
#include "PlayerMovementComponent.h"
#include "ActivityObject.h"
#include "NPC_Controller.h"

// Sets default values
ANPC_Controller::ANPC_Controller()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC_Controller::Play()
{
	if (ensure(npc) && ensure(npc->movementComponent))
	{
		///UE_LOG(LogTemp, Warning, TEXT("%s is the npc"), *npc->GetName());
		SetState(ENPCStates::IDLE);

	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("A Reference is not set."));
		return;
	}
	
}

// Called every frame
void ANPC_Controller::Tick(float DeltaTime)
{
	switch (curState)
	{
		case ENPCStates::IDLE:
			StateIdle();
			break;

		case ENPCStates::MOVE:
			StateMove();
			break;

		case ENPCStates::ATTACK:
			StateAttack();
			break;

		case ENPCStates::ATTACKPLAYER:
			StateAttackPlayer();
			break;

		case ENPCStates::DIALOGUE:
			StateDialogue();
			break;

		case ENPCStates::EVENT:
			StateEvent();
			break;

		case ENPCStates::INTOWN:
			StateInTown();
			break;

		case ENPCStates::DIE:
			StateDie();
			break;

		default:
			StateIdle();
	}
}


void ANPC_Controller::SetState(ENPCStates state)
{
	curState = state;
}

ENPCStates ANPC_Controller::GetCurState()
{
	return curState;
}

ENPCStates ANPC_Controller::GetIdleState()
{
	return ENPCStates::IDLE;
}

ENPCStates ANPC_Controller::GetMoveState()
{
	return ENPCStates::MOVE;
}

ENPCStates ANPC_Controller::GetAttackState()
{
	return ENPCStates::ATTACK;
}

ENPCStates ANPC_Controller::GetAttackPlayerState()
{
	return ENPCStates::ATTACKPLAYER;
}

ENPCStates ANPC_Controller::GetDialogueState()
{
	return ENPCStates::DIALOGUE;
}

ENPCStates ANPC_Controller::GetEventState()
{
	return ENPCStates::EVENT;
}

ENPCStates ANPC_Controller::GetInTownState()
{
	return ENPCStates::INTOWN;
}

ENPCStates ANPC_Controller::GetDieState()
{
	return ENPCStates::DIE;
}

void ANPC_Controller::NewLeadersAndFollowers(ANPC* leader, ANPC* newLeader)
{
	
	UE_LOG(LogTemp, Warning, TEXT("%s is the new leader"), *npc->GetName());
	UE_LOG(LogTemp, Warning, TEXT("%s is the old leader"), *leader->GetName());

	
	//Here we iterate through the old leader's followers. If the follower is not the new leader npc, then we set the leader of the follwer to the new leader
	//and we add that follower to the new leader's followers
	for (auto* oldFollower : leader->followers)
	{
		if (!newLeader->followers.Contains(oldFollower) && oldFollower != newLeader && !oldFollower->isDead)
		{
			oldFollower->leader = newLeader;
			newLeader->followers.Add(oldFollower);
		}
	}

	if (leader->npcController->enterEvent)
	{
		newLeader->npcController->enterEvent = true;
		newLeader->npcController->currentEventLocation = leader->npcController->currentEventLocation;
		newLeader->npcController->eventPositions = leader->npcController->eventPositions;
	}
	
	newLeader->targetDestination = leader->targetDestination;
	
	if (leader->leader)
	{
		newLeader->leader = leader->leader;
	} else
	{
		newLeader->leader = nullptr;
	}

	UE_LOG(LogTemp, Warning, TEXT("The new leader added itself to it's followers as well as added the followers"));
	
	//Here set the newLeader's leader variable to whatever the old leader's leader was, and change the isLeader boolean to true, as well as type to Champion

	//TODO Base on whether a champion goes to a follow state on whether their leader variable is empty? Change in the StateMove function

	//TODO reset maxwalkspeed
	newLeader->isLeader = true;
	newLeader->npcType = newLeader->GetChampionType();
	newLeader->movementComponent->SetDefaultState( newLeader->movementComponent->GetNullState() );

	
	UE_LOG(LogTemp, Warning, TEXT("Calling the replace leader function"));
	AWarhammerGameModeBase::ReplaceLeader(AWarhammerGameModeBase::LeaderList.Find(leader), newLeader, leader);
	
}

void ANPC_Controller::EnterDialogueState()
{
	SetState(ENPCStates::DIALOGUE);
}

void ANPC_Controller::EnterEvent(AActor* eventLocation, TArray<AActor*> positions)
{
	positionIndex = 0;
	followersEnterEvent = true;
	currentEventLocation = eventLocation;
	eventPositions = positions;
	
	UE_LOG(LogTemp, Warning, TEXT("%s has called enter event"), *npc->GetName());

	enterEvent = true;
	
}

void ANPC_Controller::StateIdle()
{
	///UE_LOG(LogTemp, Warning, TEXT("%s is idling, Is leader true?: %s"), *npc->GetName(), (npc->isLeader ? TEXT("True") : TEXT("False")));
	npc->stance = 0;

	if (npc == npc->replacementLeader)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is the replacement leader, calling the new leaders function"), *npc->GetName());
		NewLeadersAndFollowers(npc->leader, npc);
		npc->replacementLeader = nullptr;
	}
	
	if (ensure(npc->movementComponent) && npc->GetNPCType() != npc->GetCommonerType())
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement Component is set, setting state to move for %s"), *npc->GetName());
		
		if (npc->isLeader)
		{
			for (auto* follower : npc->followers)
			{
				//npc->SetActorRotation(FRotator(0, 0, 0));
				//TODO if formation position, set to nullptr, also reset all followerindices. possibly walkspeeds as well
				if (follower->movementComponent->FormationPositionActor)
				{
					follower->movementComponent->FormationPositionActor->Destroy();
				}

				follower->movementComponent->followerIndex = npc->followers.Find(follower);
				follower->movementComponent->FormationPositionActor = nullptr;
				follower->npcController->SetState(follower->npcController->GetIdleState());
				follower->movementComponent->curMoveState = follower->movementComponent->GetFollowState();
				follower->movementComponent->move = true;
			}
		}
		
		SetState(ENPCStates::MOVE);

	}else if (npc->GetNPCType() == npc->GetCommonerType())
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting %s to in Town state"), *npc->GetName());
		SetState(ENPCStates::INTOWN);

	}else
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement Component is not set (check this classes BP)"));
		return;
	}
}

//TODO create commoner state, create an array of safe locations so if the commoner gets attacked they can run away to the nearest one

void ANPC_Controller::StateMove()
{
	npc->CallMoveStateEvent();
	///UE_LOG(LogTemp, Warning, TEXT("In Move State"));

	if (npc->npcType == npc->GetCommonType() && npc->movementComponent->defaultState == npc->movementComponent->GetNullState() && !enterEvent)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Common Type called"));
		npc->movementComponent->SetDefaultState(npc->movementComponent->GetFollowState());

	}else if (npc->npcType == npc->GetChampionType() && npc->isLeader && !npc->leader && npc->movementComponent->defaultState == npc->movementComponent->GetNullState() && !enterEvent)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Champion Type called"));
		npc->movementComponent->SetDefaultState(npc->movementComponent->GetMoveToLocationState());
	
	} else if(npc->npcType == npc->GetChampionType() && npc->isLeader && npc->leader &&  npc->movementComponent->defaultState == npc->movementComponent->GetNullState() && !enterEvent)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Champion/Leader %s has a leader"), *npc->GetName());
		npc->movementComponent->SetDefaultState(npc->movementComponent->GetFollowState());
	} 
	
	if (enterEvent && npc->isLeader && !npc->movementComponent->playerTarget && !npc->movementComponent->enemyLeader && !npc->movementComponent->enemyTarget && npc->movementComponent->curMoveState != npc->movementComponent->GetMoveToBattleState() && npc->movementComponent->curMoveState != npc->movementComponent->GetMoveToEnemyState() && npc->movementComponent->curMoveState != npc->movementComponent->GetMoveToPlayerState() && npc->movementComponent->curMoveState != npc->movementComponent->GetFollowState())
	{
		///UE_LOG(LogTemp, Warning, TEXT("%s is entering the move to event state"), *npc->GetName());
		npc->movementComponent->curMoveState = npc->movementComponent->GetMoveToEventState();
		npc->npcController->MoveToActor(currentEventLocation);
		enterEvent = false;
	}

	npc->movementComponent->MoveAI(npc);
}

void ANPC_Controller::StateAttack()
{
	
	//Here the npc should be moving to enemy until they can attack. Right now this is only called when the npc actually attacks

	//Here we run through the combat function until either this npc dies, or their opponent dies. If their opponent dies, then they set this npc's enemyTarget to null, so that this npc can resume

	if (npc->movementComponent->enemyTarget && npc->movementComponent->enemyTarget->npcHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Enemy target of %s is dead, going to state MOVE."), *npc->movementComponent->enemyTarget->GetName(), *npc->GetName());
		npc->killCount++;
		npc->movementComponent->confrontation = false;
		npc->movementComponent->enemyTarget = nullptr;
		SetState(ENPCStates::MOVE);

	} else if (!npc->movementComponent->enemyTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy target of %s is null, in attack state"), *npc->GetName());
		//TODO greenskin common got stuck here attempting to fight the dwarf leader, who then fought the other leader. Flee move state worked correctly though

	} else if (npc->movementComponent->enemyTarget && npc->movementComponent->enemyTarget->npcController->curState != ENPCStates::ATTACK)
	{
		UE_LOG(LogTemp, Warning, TEXT("The enemy of %s, %s, is not in the attack state."), *npc->GetName(), *npc->movementComponent->enemyTarget->GetName());
		SetState(ENPCStates::MOVE);

	} else if (npc->movementComponent->enemyTarget && npc->movementComponent->enemyTarget->movementComponent->enemyTarget != npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("The enemy of %s, %s, has a different target."), *npc->GetName(), *npc->movementComponent->enemyTarget->GetName());
		

	}
	
	if (npc->npcHealth <= 0)
	{
		SetState(ENPCStates::DIE);

	}else if (npc->canAttack && npc->movementComponent->confrontation && npc->npcHealth > 0 && ensure(npc->movementComponent->enemyTarget) && npc->movementComponent->enemyTarget->npcHealth > 0)
	{
		///UE_LOG(LogTemp, Warning, TEXT("%s is attacking %s"), *npc->GetName(), *npc->movementComponent->enemyTarget->GetName());
		//TODO if combat list removes the two npc's fighting after the function runs through every time, then if the player moves away and doesn't call the attack function, then the npc won't attack
		UCombat::Attack(npc, npc->movementComponent->enemyTarget);
	}
}

void ANPC_Controller::StateAttackPlayer()
{
	npc->inAttackState();
	FVector distanceToPlayer;

	if (!npc->movementComponent->playerTarget)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Enemy target null of %s, going to state IDLE."), *npc->GetName());
		/*
		npc->killCount++;
		npc->movementComponent->confrontation = false;
		SetState(ENPCStates::MOVE);
		*/
		if (npc->leader->movementComponent->playerTarget)
		{
			PlayerLockOn(npc->leader->movementComponent->playerTarget);

		} else
		{
			PlayerLockOn(npc->leader);
		}
	} else
	{
		distanceToPlayer = npc->GetActorLocation() - npc->movementComponent->playerTarget->GetActorLocation();

		//TODO add inmovestate event so npc's walk

		PlayerLockOn(npc->movementComponent->playerTarget);

		if (npc->movementComponent->playerTarget->ForwardMovement != 0.0f && distanceToPlayer.Size() < 500.0f)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Moving Forwards or backwards"));
			//move forward
			float forwardMovement = npc->movementComponent->playerTarget->ForwardMovement / 10;
			const FVector Direction = FRotationMatrix(npc->GetActorRotation()).GetScaledAxis(EAxis::X);

			npc->AddMovementInput(Direction, forwardMovement * GetWorld()->GetDeltaSeconds());

		} else if (npc->movementComponent->playerTarget->SideMovement != 0.0f)
		{
			// move sideways

			float sideMovement = npc->movementComponent->playerTarget->SideMovement * 0.05f;

			const FRotator Rotation = npc->GetActorRotation();
			const FRotator YawRotation(0, Rotation.Yaw + (-1.1 * sideMovement ), 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);
			// add movement in that direction
			npc->AddMovementInput(Direction, sideMovement / 20);

		} else if (distanceToPlayer.Size() > 500.0f)
		{
			float forwardMovement = 100.0f;
			const FVector Direction = FRotationMatrix(npc->GetActorRotation()).GetScaledAxis(EAxis::X);

			npc->AddMovementInput(Direction, forwardMovement * GetWorld()->GetDeltaSeconds());
		}

		

	}

	if (npc->npcHealth <= 0)
	{
		SetState(ENPCStates::DIE);

	} else if (!UCombat::CombatList.Contains(npc))
	{
		///UE_LOG(LogTemp, Warning, TEXT("%s is attacking %s"), *npc->GetName(), *npc->movementComponent->playerTarget->GetName());
		//TODO change this so that the attack only runs through once per
		//UE_LOG(LogTemp, Warning, TEXT("Distance to player: %f"), distanceToPlayer.Size());
		//UCombat::AttackPlayer(npc, npc->movementComponent->playerTarget);
	}

}

void ANPC_Controller::StateDialogue()
{
	if (npc->GetVelocity().Size() > 0)
	{
		//TODO get rid of dialogue state, replace with bool and function to check npc constraints, like if they are in follow state, etc;
		//npc->movementComponent->DisableMovement();
		npc->movementComponent->StopActiveMovement();
		npc->CreateDialogue();
		UE_LOG(LogTemp, Warning, TEXT("Velocity X: %f"), npc->GetVelocity().Size());
	}
}

void ANPC_Controller::StateEvent()
{
	if (npc->GetNPCRace() == npc->GetDwarfRace() && !AWarhammerGameModeBase::dwarfEventList.Contains(npc))
	{
		AWarhammerGameModeBase::dwarfEventList.Add(npc);
		///UE_LOG(LogTemp, Warning, TEXT("Adding %s to the dwarf Event List"), *npc->GetName());

	} else if (npc->GetNPCRace() == npc->GetGreenskinRace() && !AWarhammerGameModeBase::greenskinEventList.Contains(npc))
	{
		AWarhammerGameModeBase::greenskinEventList.Add(npc);
		///UE_LOG(LogTemp, Warning, TEXT("Adding %s to the greenskin Event List"), *npc->GetName());
	}

	FVector distance;
	distance = npc->GetActorLocation() - currentEventLocation->GetActorLocation();
	int eventDistanceLength = distance.Size();

	///UE_LOG(LogTemp, Warning, TEXT("The distance to the event position is %d."), eventDistanceLength);

	if (eventDistanceLength < 120 && !atEventPosition)
	{
		///UE_LOG(LogTemp, Warning, TEXT("%s is at their position"), *npc->GetName());
		//add a boolean here that switches to true, in the end event function check if all booleans are true. Could use an int and check if it's equal to EvenList.Num()
		atEventPosition = true;

		if (npc->GetNPCRace() == npc->GetDwarfRace())
		{
			AWarhammerGameModeBase::dwarfEventCount += 1;
			UE_LOG(LogTemp, Warning, TEXT("Dwarf Event Count is %d, while the Event List Num() is %d"), AWarhammerGameModeBase::dwarfEventCount, AWarhammerGameModeBase::dwarfEventList.Num());
		
		} else if (npc->GetNPCRace() == npc->GetGreenskinRace())
		{
			AWarhammerGameModeBase::greenskinEventCount += 1;
			UE_LOG(LogTemp, Warning, TEXT("Greenskin Event Count is %d, while the Event List Num() is %d"), AWarhammerGameModeBase::greenskinEventCount, AWarhammerGameModeBase::greenskinEventList.Num());
		}

		AWarhammerGameModeBase::EndEvent(npc);
		positionIndex = 0;
	}

	//TODO make sure to reset default move state once event is over, or current?
	if (followersEnterEvent)
	{
		///UE_LOG(LogTemp, Warning, TEXT("%s is in the event State"), *npc->GetName());
		///UE_LOG(LogTemp, Warning, TEXT("%s is about to check followers"), *npc->GetName());

		//Here we'll check if a position in the positions array passed by WorldEvents, the original array located in the WarhammerGameModeBase
		//This will be where the leader loops through their followers, setting moving them to their position and setting their state to event
		for (auto* follower : npc->followers)
		{
			//If it isn't vacant, then we increase the index to check the next position
			for (auto* position : eventPositions)
			{
				
				if (positionIndex <= eventPositions.Num() && eventPositions.IsValidIndex(positionIndex))
				{
					PositionVacant(eventPositions[positionIndex]);

					if (!vacant)
					{
						///UE_LOG(LogTemp, Warning, TEXT("This position is not vacant for %s while looking at %s, increasing index"), *npc->GetName(), *follower->GetName());
						positionIndex++;

					} else
					{
						//when a position is vacant, then we'll send the follower there and break the position for-loop to continue on to the next follower
						UE_LOG(LogTemp, Warning, TEXT("This position is vacant, sending %s to a position"), *follower->GetName());
						OccupyPosition(eventPositions[positionIndex]);
						follower->npcController->currentEventLocation = eventPositions[positionIndex];
						follower->npcController->MoveToActor(follower->npcController->currentEventLocation);
						follower->npcController->SetState(ENPCStates::EVENT);
						break;
					}
				}else
				{
					//If the index of the positions array is invalid, send them to an alternate location.
					UE_LOG(LogTemp, Warning, TEXT("This position for %s is not valid"), *follower->GetName());

				}
			}
		}

		followersEnterEvent = false;
	}else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Followers enter event for %s is false"), *npc->GetName());
	}
}

void ANPC_Controller::StateInTown()
{
	if (npc->currentLocation)
	{
		npc->currentLocation->AddNPC(npc);
	}

	/*
		TODO create function for timer that returns bool to indicate when to move to next activity

		if activity
			if not at activity
				cur move state move to activity
				move ai

			if at activity
				call function to play start animation to loop animation section

			if timer for next activity
				call function to play finish section
	*/

	//timer function, while i < time return true, called from locations

	if (npc->activity)
	{
		if (!npc->movementComponent->atActivity)
		{
			UE_LOG(LogTemp, Warning, TEXT("Moving to activity"));
			npc->movementComponent->curMoveState = npc->movementComponent->GetMoveToActivityState();
			npc->npcController->SetState(ENPCStates::MOVE);
		
		} else if (!npc->inActivity && npc->activity->GetAngleFromActivity(npc))		
		{
			//TODO solve why this is being skipped. Perhaps copy above param below
			npc->activity->activityNPC = npc;
			npc->activity->FaceActivity();

		} else if(!npc->inActivity)
		{

			npc->inActivity = true;
			npc->StartActivityEvent();
			npc->activityTime = 0.0f;
			UE_LOG(LogTemp, Warning, TEXT("Starting activity"));

		} else
		{
			//Here I can call a function to play one off animations
		}
	} 
}

void ANPC_Controller::StateDie()
{
	//Changes this npc's death bool to true so that anyone colliding with/any arrays it's in will read it's dead, then ignore or remove it.
	//TODO change this procedure into an actual method callable from any script with an array, where it asks for an item to remove as a parameter, then removes it, that way it is only called once from any npc that dies.
	//Also sets the enemyTarget of the npc that targeted this one to null, so that npc will reset to Idle.
	
	npc->isDead = true;
	//npc->isLeader = false;
	///UE_LOG(LogTemp, Warning, TEXT("%s has died"), *npc->GetName());

	if (npc->dwarf)
	{
		GameMode->SetDeadNPCs(ANPC::GetDwarfRace(), 1);
		
		UE_LOG(LogTemp, Warning, TEXT("The number of dead dwarfs is: %d, and the number of dead greenskins is: %d."), GameMode->deadDwarfs, GameMode->deadGreenskins);
	}
	if (npc->greenskin)
	{
		GameMode->SetDeadNPCs(ANPC::GetGreenskinRace(), 1);
		
		UE_LOG(LogTemp, Warning, TEXT("The number of dead dwarfs is: %d, and the number of dead greenskins is: %d."), GameMode->deadDwarfs, GameMode->deadGreenskins);
	}

	/*
		if npc is not a leader and has enemy target, then we will set the target of the enemy target to a follower or an npc +- 1 in the follower index
		if the enemy target has a follower as well, we will set their enemy target through a similar formula as the first
	*/
	if (npc->movementComponent->enemyTarget && !npc->isLeader)
	{
		npc->FindTarget(npc, npc->movementComponent->battleFollower, npc->movementComponent->enemyTarget, npc->movementComponent->enemyTarget->movementComponent->battleFollower);
	}

	if (npc->isLeader)
	{
		npc->movementComponent->enemyLeader->movementComponent->enemyLeader = nullptr;

		if (npc->movementComponent->enemyTarget)
		{
			npc->movementComponent->enemyTarget->movementComponent->enemyTarget = nullptr;
		}

		for (auto* follower : npc->followers)
		{	
			UE_LOG(LogTemp, Warning, TEXT("Setting %s to flee"), *follower->GetName());
			follower->leader = nullptr;
			follower->movementComponent->enemyTarget = nullptr;
			follower->targetDestination = npc->targetDestination;
			follower->previousLocation = npc->previousLocation;
			follower->waypoint = npc->currentLocation;
			//follower->npcController->MoveToActor(follower->waypoint);
			follower->movementComponent->locationTimer = 60;
			follower->movementComponent->curMoveState = follower->movementComponent->GetFleeState();
		}
	}

	if (npc->movementComponent->FormationPositionActor)
	{
		npc->movementComponent->FormationPositionActor->Destroy();
	}

	if (npc->movementComponent->playerTarget)
	{
		npc->movementComponent->playerTarget->movementComponent->enemyTarget = nullptr;
		
		if (npc->movementComponent->playerTarget->movementComponent->Enemies.Contains(npc))
		{
			npc->movementComponent->playerTarget->movementComponent->Enemies.Remove(npc);
		}
	}

	if (npc->leader)
	{
		npc->leader->followers.Remove(npc);
	}

	//TODO if npc is in player array when dies remove from array

	if (enterEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("calling remove from event %s"), *npc->GetName());
		AWarhammerGameModeBase::RemoveFromEvent(npc);
	}

	

	npc->SetActorEnableCollision(false);
	//npc->GetRootComponent()->SetWorldRotation(FRotator(0, 90, 0));
	//FVector newLocation = (npc->GetActorLocation(), npc->GetActorLocation(), npc->GetActorLocation() - 80);

	//npc->SetActorLocation(newLocation);

	//npc->Destroy();
	
	SetActorTickEnabled(false);
}


//TODO test combat with multiple npcs to fine tune stats
//TODO dialogue function that returns true if one of the game mode bools are true, then each bool is assigned a number
//RandRange up to the max, and when the function is called with a number greater than 0(so that we don't call the dialogue from the if)
//have that bools associated dialogues play

