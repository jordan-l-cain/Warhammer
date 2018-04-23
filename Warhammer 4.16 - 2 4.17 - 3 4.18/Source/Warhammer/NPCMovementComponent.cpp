// Fill out your copyright notice in the Description page of Project Settings.

#include "Warhammer.h"
#include "NPC.h"
#include "NPC_Controller.h"
#include "Player_Char.h"
#include "PlayerMovementComponent.h"
#include "WarhammerGameModeBase.h"
#include "Locations.h"
#include "ActivityObject.h"
#include "NPCMovementComponent.h"


void UNPCMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	originalRotation = GetOwner()->GetActorRotation();
}

void UNPCMovementComponent::MoveAI(ANPC* npc)
{

	switch (curMoveState)
	{
		case EMoveStates::MOVETOLOCATION:
			MoveToLocation(npc);
			break;

		case EMoveStates::FOLLOW:
			Follow(npc);
			break;

		case EMoveStates::MOVETOENEMY:
			MoveToEnemy(npc);
			break;

		case EMoveStates::MOVETOBATTLE:
			MoveToBattle(npc);
			break;

		case EMoveStates::MOVETOEVENT:
			MoveToEvent(npc);
			break;

		case EMoveStates::MOVETOACTIVITY:
			MoveToActivity(npc);
			break;

		case EMoveStates::MOVETOPLAYER:
			MoveToPlayer(npc);
			break;

		case EMoveStates::FLEE:
			Flee(npc);
			break;

		case EMoveStates::NULLMOVE:
			curMoveState = defaultState;
	}

}

void UNPCMovementComponent::MoveToLocation(ANPC* npc)
{
	///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, trying to move to location."), *npc->GetName());
	if (!gameMode)
	{
		gameMode = Cast<AWarhammerGameModeBase>(GetWorld()->GetAuthGameMode());
	}

	if (npc->currentLocation)
	{
		if (!npc->targetDestination)
		{

			///UE_LOG(LogTemp, Warning, TEXT("Game mode is valid"));
			//gameMode->SetTravelLocationEvent(npc);
			if (npc->GetNPCRace() == ANPC::GetDwarfRace())
			{
				npc->previousLocation = npc->currentLocation;

				npc->targetDestination = ALocations::GetDestination(npc->currentLocation, true);
				npc->currentLocation = npc->targetDestination;
				/*
					given a destination, find the array(value) in the tmap associated to that destination by using the previous locations array, with a key of target location
					set the first index of that array as the destination

					So if npc is at grimn kairn currently, and their target destination is grimn gon
					using grimn gon as a key of grimn kairns locations array, get the associated array
					with the associated array, set the waypoint as the first index of that array
				*/
				npc->waypoint = npc->previousLocation->locationArrays[npc->targetDestination->location].locations[0];

			}

			if (npc->GetNPCRace() == ANPC::GetGreenskinRace())
			{
				npc->previousLocation = npc->currentLocation;

				npc->targetDestination = ALocations::GetDestination(npc->currentLocation, false);
				npc->currentLocation = npc->targetDestination;

				npc->waypoint = npc->previousLocation->locationArrays[npc->targetDestination->location].locations[0];
			}
		}

		MaxWalkSpeed = 400;
		locationTimer++;

		if (playerTarget)
		{
			/*
			//this int will be used to set the followers
			int i = 0;

			if (playerTarget->followers.Num() > 0)
			{
				for (auto* enemyFollower : playerTarget->followers)
				{
					if (enemyFollower->movementComponent->followerIndex < 10)
					{
						if (!playerTarget->movementComponent->enemyTarget)
						{
							playerTarget->movementComponent->enemyTarget = npc->followers[enemyFollower->movementComponent->followerIndex];
						}

						UE_LOG(LogTemp, Warning, TEXT("setting two followers as enemies at index of %d, enemy follower is %s and ally follower is %s"), enemyFollower->movementComponent->followerIndex, *enemyFollower->GetName(), *npc->followers[enemyFollower->movementComponent->followerIndex]->GetName());

						npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->enemyTarget = enemyFollower;
						npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->curMoveState = GetMoveToBattleState();
						npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->move = true;

						enemyFollower->movementComponent->enemyTarget = npc->followers[enemyFollower->movementComponent->followerIndex];
						enemyFollower->movementComponent->curMoveState = GetMoveToBattleState();
						enemyFollower->movementComponent->move = true;

						continue;

					} else
					{
						UE_LOG(LogTemp, Warning, TEXT("setting follower target of enemy follower %s to %s"), *enemyFollower->GetName(), *enemyLeader->followers[i]->GetName());

						enemyFollower->movementComponent->followTarget = enemyLeader->followers[i];
						enemyLeader->followers[i]->movementComponent->battleFollower = enemyFollower;
						enemyFollower->movementComponent->curMoveState = GetMoveToBattleState();
						enemyFollower->movementComponent->move = true;

						if (enemyFollower->movementComponent->followerIndex < npc->followers.Num())
						{
							UE_LOG(LogTemp, Warning, TEXT("setting follower target of friendly follower %s to %s, at an index of %d"), *npc->followers[enemyFollower->movementComponent->followerIndex]->GetName(), *npc->followers[i]->GetName(), enemyFollower->movementComponent->followerIndex);


							//TODO solve why last dwarves don't have a follower or a target
							npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->followTarget = npc->followers[i];
							npc->followers[i]->movementComponent->battleFollower = npc->followers[enemyFollower->movementComponent->followerIndex];
							npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->curMoveState = GetMoveToBattleState();
							npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->move = true;
						}

						i++;
					}
				}
			} else
			{
				for (auto* follower : npc->followers)
				{
					if (!playerTarget->movementComponent->enemyTarget)
					{
						playerTarget->movementComponent->enemyTarget = follower;
						follower->movementComponent->curMoveState = GetMoveToBattleState();
						follower->movementComponent->move = true;

					} else
					{
						follower->movementComponent->followTarget = npc->followers[i];
						npc->followers[i]->movementComponent->battleFollower = follower;
						follower->movementComponent->curMoveState = GetMoveToBattleState();
						follower->movementComponent->move = true;
						i++;
					}
				}
			}
			*/

			npc->npcController->MoveToActor(playerTarget);
			curMoveState = EMoveStates::MOVETOPLAYER;

			/*

			if leader has no followers
				attack player

			else
				If this leader npc is not in combat
					have this leader's followers form a circle around player
						avoid center while moving in circle
							create a collider on the player that only the enemies they've put through the filter don't collide with
					take input from player to determine who will attack player next up to 5 followers
						send those five at the player

				if leader is in combat
					take input from player to determine who will attack player next up to 5 followers
						send those five at the player

			*/
		}

		if (!enemyLeader && npc->targetDestination)
		{
			///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, does not have an enemy leader. Moving at %f"), *npc->GetName(), npc->movementComponent->Velocity.Size());

			moveToLeader = true;

			if (locationTimer >= 60)
			{
				
				if (moveToLocation)
				{
					///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, is moving to their waypoint"), *npc->GetName());
					npc->npcController->MoveToActor(npc->waypoint);
					moveToLocation = false;
				}

				FVector waypointDistance = npc->GetActorLocation() - npc->waypoint->GetActorLocation();

				if (waypointDistance.Size() < 8000)
				{
					ALocations::nextWaypoint(npc);

					moveToLocation = true;
				}

				///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, about to search for enemy leaders."), *npc->GetName());
				for (auto* actor : AWarhammerGameModeBase::LeaderList)
				{
					///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, has found at least one enemy leader"), *npc->GetName());

					if (npc->GetNPCRace() != actor->GetNPCRace() && !actor->isDead)
					{
						FVector leaderDistance = npc->GetActorLocation() - actor->GetActorLocation();

						if (leaderDistance.Size() <= 10000)
						{
							//TODO could use middle point .y for the leader, or middle point between first npc in followers and last
							middlePoint = (npc->GetActorLocation() + actor->GetActorLocation()) / 2;

							for (auto* follower : npc->followers)
							{
								follower->movementComponent->middlePoint = middlePoint;
							}

							enemyLeader = actor;
						}
					}
				}

				locationTimer = 0;

				if (npc->GetVelocity().Size() <= 0)
				{
					moveToLocation = true;
				}
			}
		} else if (enemyLeader)
		{
			UE_LOG(LogTemp, Warning, TEXT("This npc is %s, has an enemy leader target"), *npc->GetName());

			locationTimer = 0;
			moveToLocation = true;
			npc->npcController->StopMovement();

			//The leader with the smaller unit will be the one to set the targets 
			if (npc->followers.Num() < enemyLeader->followers.Num())
			{
				//TODO turn this into a function that can be called after an animation, make followers get into a formation if dwarfs
				//reason being for leaders to give boasts and proclamations before charging to battle
				//this int will be used to set the followers
				int i = 0;

				for (auto* enemyFollower : enemyLeader->followers)
				{
					if (enemyFollower->movementComponent->followerIndex < 10)
					{
						UE_LOG(LogTemp, Warning, TEXT("setting two followers as enemies at index of %d, enemy follower is %s and ally follower is %s"), enemyFollower->movementComponent->followerIndex, *enemyFollower->GetName(), *npc->followers[enemyFollower->movementComponent->followerIndex]->GetName());

						npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->enemyTarget = enemyFollower;
						npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->curMoveState = GetMoveToBattleState();
						npc->followers[enemyFollower->movementComponent->followerIndex]->npcController->SetState(ENPCStates::MOVE);
						npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->move = true;

						enemyFollower->movementComponent->enemyTarget = npc->followers[enemyFollower->movementComponent->followerIndex];
						enemyFollower->movementComponent->curMoveState = GetMoveToBattleState();
						enemyFollower->npcController->SetState(ENPCStates::MOVE);
						enemyFollower->movementComponent->move = true;

						continue;

					} else
					{
						UE_LOG(LogTemp, Warning, TEXT("setting follower target of enemy follower %s to %s"), *enemyFollower->GetName(), *enemyLeader->followers[i]->GetName());
						enemyFollower->movementComponent->followTarget = enemyLeader->followers[i];
						enemyLeader->followers[i]->movementComponent->battleFollower = enemyFollower;
						enemyLeader->followers[i]->npcController->SetState(ENPCStates::MOVE);
						enemyFollower->movementComponent->curMoveState = GetMoveToBattleState();
						enemyFollower->npcController->SetState(ENPCStates::MOVE);
						enemyFollower->movementComponent->move = true;

						if (enemyFollower->movementComponent->followerIndex < npc->followers.Num())
						{
							UE_LOG(LogTemp, Warning, TEXT("setting follower target of friendly follower %s to %s, at an index of %d"), *npc->followers[enemyFollower->movementComponent->followerIndex]->GetName(), *npc->followers[i]->GetName(), enemyFollower->movementComponent->followerIndex);

							npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->followTarget = npc->followers[i];
							npc->followers[i]->movementComponent->battleFollower = npc->followers[enemyFollower->movementComponent->followerIndex];
							npc->followers[i]->npcController->SetState(ENPCStates::MOVE);
							npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->curMoveState = GetMoveToBattleState();
							npc->followers[enemyFollower->movementComponent->followerIndex]->npcController->SetState(ENPCStates::MOVE);
							npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->move = true;
						}

						i++;
					}
				}
			} else if (npc->GetNPCRace() == ANPC::GetDwarfRace())
			{
				//this int will be used to set the followers
				int i = 0;

				for (auto* enemyFollower : enemyLeader->followers)
				{
					if (enemyFollower->movementComponent->followerIndex < 10)
					{
						UE_LOG(LogTemp, Warning, TEXT("setting two followers as enemies at index of %d, enemy follower is %s and ally follower is %s"), enemyFollower->movementComponent->followerIndex, *enemyFollower->GetName(), *npc->followers[enemyFollower->movementComponent->followerIndex]->GetName());

						npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->enemyTarget = enemyFollower;
						npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->curMoveState = GetMoveToBattleState();
						npc->followers[enemyFollower->movementComponent->followerIndex]->npcController->SetState(ENPCStates::MOVE);
						npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->move = true;

						enemyFollower->movementComponent->enemyTarget = npc->followers[enemyFollower->movementComponent->followerIndex];
						enemyFollower->movementComponent->curMoveState = GetMoveToBattleState();
						enemyFollower->npcController->SetState(ENPCStates::MOVE);
						enemyFollower->movementComponent->move = true;

						continue;

					} else
					{
						UE_LOG(LogTemp, Warning, TEXT("setting follower target of enemy follower %s to %s"), *enemyFollower->GetName(), *enemyLeader->followers[i]->GetName());
						enemyFollower->movementComponent->followTarget = enemyLeader->followers[i];
						enemyLeader->followers[i]->movementComponent->battleFollower = enemyFollower;
						enemyLeader->followers[i]->npcController->SetState(ENPCStates::MOVE);
						enemyFollower->movementComponent->curMoveState = GetMoveToBattleState();
						enemyFollower->npcController->SetState(ENPCStates::MOVE);
						enemyFollower->movementComponent->move = true;

						if (enemyFollower->movementComponent->followerIndex < npc->followers.Num())
						{
							UE_LOG(LogTemp, Warning, TEXT("setting follower target of friendly follower %s to %s, at an index of %d"), *npc->followers[enemyFollower->movementComponent->followerIndex]->GetName(), *npc->followers[i]->GetName(), enemyFollower->movementComponent->followerIndex);

							npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->followTarget = npc->followers[i];
							npc->followers[i]->movementComponent->battleFollower = npc->followers[enemyFollower->movementComponent->followerIndex];
							npc->followers[i]->npcController->SetState(ENPCStates::MOVE);
							npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->curMoveState = GetMoveToBattleState();
							npc->followers[enemyFollower->movementComponent->followerIndex]->npcController->SetState(ENPCStates::MOVE);
							npc->followers[enemyFollower->movementComponent->followerIndex]->movementComponent->move = true;
						}

						i++;
					}
				}
			}

			npc->followerCount = npc->followers.Num();
			curMoveState = GetMoveToBattleState();
		}

	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have a current location"), *npc->GetName());
	}
}

void UNPCMovementComponent::Follow(ANPC* npc)
{
	///UE_LOG(LogTemp, Warning, TEXT("This npc: %s, is trying to follow."), *npc->GetName());
	
	if (npc->playerLeader)
	{
		if(!npc->playerLeader->followers.Contains(npc))
		{
			npc->playerLeader->followers.Add(npc);

			followerIndex = npc->playerLeader->followers.Find(npc);
		}

		FVector formationPosition;
		float distanceToPosition = 0;
		int formationIndex;


		if (followerIndex < 10)
		{
			//We take away increments of 10 starting at -5 so that we can do formationIndex * spacebetween, so that the followers will center automatically
			formationIndex = followerIndex - 3;
			//plus followerindex * 100 * randnumber( 2,3) for greenskins, to give a more random formation appearance

			formationPosition.X = -1000;

		} else if (followerIndex < 20 && followerIndex > 9)
		{
			formationIndex = followerIndex - 15;
			formationPosition.X = -2000;

		} else if (followerIndex < 30 && followerIndex > 19)
		{
			formationIndex = followerIndex - 25;
			formationPosition.X = -3000;

		} else if (followerIndex < 40 && followerIndex > 29)
		{
			formationIndex = followerIndex - 35;
			formationPosition.X = -4000;
		} else
		{
			formationIndex = followerIndex - 45;
			formationPosition.X = -5000;
		}

		if (npc->GetNPCRace() == ANPC::GetDwarfRace())
		{
			formationPosition.Y = (-formationIndex * 350);
			formationPosition.Z = 0;

			if (FormationPositionActor)
			{
				distanceToPosition = FVector::Distance(npc->GetActorLocation(), FormationPositionActor->GetActorLocation());

			} else
			{
				distanceToPosition = 0;
			}
		}

		if (npc->GetNPCRace() == ANPC::GetGreenskinRace())
		{
			formationPosition.Y = (formationIndex * 500);
			formationPosition.Z = 0;

			if (FormationPositionActor)
			{
				distanceToPosition = FVector::Distance(npc->GetActorLocation(), FormationPositionActor->GetActorLocation());

			} else
			{
				distanceToPosition = 0;
			}
		}

		//This was the original maxwalkspeed, but changing it to the below increased the number of npcs that would be immediately at their position



		if (move)
		{
			//If this npc doesn't have a formation position, then spawn an actor at it's calculated position
			if (FormationPositionActor)
			{
				npc->npcController->MoveToActor(FormationPositionActor);
				///UE_LOG(LogTemp, Warning, TEXT("%s moved to actor at %s."), *npc->GetName(), *FormationPositionActor->GetActorLocation().ToString());

				move = false;

				//TODO add velocity check so that the formation positions aren's spawned in an arc
			} else
			{
				enemyTarget = nullptr;
				followTarget = nullptr;
				battleFollower = nullptr;

				UE_LOG(LogTemp, Warning, TEXT("Actor under leader was not created, creating now"));
				FActorSpawnParameters SpawnInfo;
				FormationPositionActor = Cast<AActor>(GetWorld()->SpawnActor<AActor>(FormationPositionBP, formationPosition, FRotator(0.0f, 0.0f, 0.0f), SpawnInfo));
				//attach the formation actor so that we do not have to constantly set it's transform
				FormationPositionActor->AttachToActor(npc->playerLeader, FAttachmentTransformRules::KeepWorldTransform);
				FormationPositionActor->SetActorRelativeLocation(formationPosition);
			}
		}


		if (distanceToPosition > 750)
		{
			MaxWalkSpeed = npc->playerLeader->movementComponent->MaxWalkSpeed + 100;

		} else
		{

			MaxWalkSpeed = npc->playerLeader->movementComponent->MaxWalkSpeed - 100 + (distanceToPosition * 0.25);
		}

		MaxWalkSpeed = FMath::Clamp(MaxWalkSpeed, 0.0f, (npc->playerLeader->movementComponent->MaxWalkSpeed + 100));

		if (npc->movementComponent->Velocity.Size() <= 0 && FMath::Abs(npc->playerLeader->movementComponent->Velocity.Size()) > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Move is complete but leader is still moving"));
			move = true;

		} else if (npc->movementComponent->Velocity.Size() <= 0 && FMath::Abs(npc->playerLeader->movementComponent->Velocity.Size()) <= 0)
		{
			///UE_LOG(LogTemp, Warning, TEXT("This npc is not moving and says the leader is not as well from %s"), *npc->GetName());
		}

	}else if (npc->leader)
	{
		FVector formationPosition;
		float distanceToPosition = 0;
		int formationIndex;

		if (followerIndex < 10)
		{
			//We take away increments of 10 starting at -5 so that we can do formationIndex * spacebetween, so that the followers will center automatically
			formationIndex = followerIndex - 5;
			//plus followerindex * 100 * randnumber( 2,3) for greenskins, to give a more random formation appearance

			formationPosition.X = -1000;

		} else if (followerIndex < 20 && followerIndex > 9)
		{
			formationIndex = followerIndex - 15;
			formationPosition.X = -2000;

		} else if (followerIndex < 30 && followerIndex > 19)
		{
			formationIndex = followerIndex - 25;
			formationPosition.X = -3000;

		} else if (followerIndex < 40 && followerIndex > 29)
		{
			formationIndex = followerIndex - 35;
			formationPosition.X = -4000;
		} else
		{
			formationIndex = followerIndex - 45;
			formationPosition.X = -5000;
		}

		if (npc->GetNPCRace() == ANPC::GetDwarfRace())
		{
			formationPosition.Y = (-formationIndex * 350);
			formationPosition.Z = 0;

			if (FormationPositionActor)
			{
				distanceToPosition = FVector::Distance(npc->GetActorLocation(), FormationPositionActor->GetActorLocation());

			} else
			{
				distanceToPosition = 0;
			}
		}

		if (npc->GetNPCRace() == ANPC::GetGreenskinRace())
		{
			formationPosition.Y = (formationIndex * 500);
			formationPosition.Z = 0;

			if (FormationPositionActor)
			{
				distanceToPosition = FVector::Distance(npc->GetActorLocation(), FormationPositionActor->GetActorLocation());

			} else
			{
				distanceToPosition = 0;
			}
		}

		//This was the original maxwalkspeed, but changing it to the below increased the number of npcs that would be immediately at their position
	
		if (move)
		{
			//If this npc doesn't have a formation position, then spawn an actor at it's calculated position
			if (FormationPositionActor)
			{
				npc->npcController->MoveToActor(FormationPositionActor);
				///UE_LOG(LogTemp, Warning, TEXT("%s moved to actor at %s."), *npc->GetName(), *FormationPositionActor->GetActorLocation().ToString());

				move = false;

			} else
			{
				enemyTarget = nullptr;
				followTarget = nullptr;
				battleFollower = nullptr;

				///UE_LOG(LogTemp, Warning, TEXT("Actor under leader was not created, creating now"));
				FActorSpawnParameters SpawnInfo;
				FormationPositionActor = Cast<AActor>(GetWorld()->SpawnActor<AActor>(FormationPositionBP, formationPosition, FRotator(0.0f, 0.0f, 0.0f), SpawnInfo));
				//attach the formation actor so that we do not have to constantly set it's transform
				FormationPositionActor->AttachToActor(npc->leader, FAttachmentTransformRules::KeepWorldTransform);
				FormationPositionActor->SetActorRelativeLocation(formationPosition);
			}
		}
		
		if (distanceToPosition > 750)
		{
			MaxWalkSpeed = npc->leader->movementComponent->MaxWalkSpeed + 100;

		} else
		{

			MaxWalkSpeed = npc->leader->movementComponent->MaxWalkSpeed - 100 + (distanceToPosition * 0.25);
		}

		MaxWalkSpeed = FMath::Clamp(MaxWalkSpeed, 0.0f, (npc->leader->movementComponent->MaxWalkSpeed + 100));

		if (npc->movementComponent->Velocity.Size() <= 0 && FMath::Abs(npc->leader->movementComponent->Velocity.Size()) > 0)
		{
			///UE_LOG(LogTemp, Warning, TEXT("Move is complete but leader is still moving"));
			move = true;

		} else if (npc->movementComponent->Velocity.Size() <= 0 && FMath::Abs(npc->leader->movementComponent->Velocity.Size()) <= 0)
		{
			///UE_LOG(LogTemp, Warning, TEXT("This npc is not moving and says the leader is not as well from %s"), *npc->GetName());
		}
		
	} else if(!npc->leader && !npc->playerLeader)
	{
		UE_LOG(LogTemp, Warning, TEXT("The common npc does not have a leader"));
	}
}

void UNPCMovementComponent::MoveToBattle(ANPC* npc)
{
	///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, entering move to battle state."), *npc->GetName());
	//TODO fix leader centering on formation, needs x and y location

	if (npc->isLeader)
	{
		if (!enemyLeader || enemyLeader->isDead)
		{
			//TODO solve why former formation positions didn't get destroyed and indices reset.
			npc->npcController->curState = npc->npcController->GetIdleState();
			curMoveState = EMoveStates::MOVETOLOCATION;
			enemyLeader = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("%s is going to idle"), *npc->GetName());
		} else
		{

			if (npc->movementComponent->Velocity.Size() <= 0)
			{
				///UE_LOG(LogTemp, Warning, TEXT("%s is moving to middle follower"), *npc->GetName());
				npc->npcController->MoveToLocation(FVector(npc->followers[FMath::Abs(npc->followers.Num() / 2)]->GetActorLocation().X, npc->GetActorLocation().Y, npc->GetActorLocation().Z));
			}

			if (enemyTarget && npc->followers.Num() > (npc->followerCount / 2))
			{
				///UE_LOG(LogTemp, Warning, TEXT("%s is moving to attack %s"), *npc->GetName(), *enemyTarget->GetName());
				npc->npcController->MoveToActor(enemyTarget);
				curMoveState = EMoveStates::MOVETOENEMY;
			}

			if (npc->followers.Num() < (npc->followerCount / 2))
			{
				enemyTarget = enemyLeader;
				enemyLeader->movementComponent->enemyTarget = npc;

				UE_LOG(LogTemp, Warning, TEXT("%s is moving to attack %s"), *npc->GetName(), *enemyTarget->GetName());

				for (auto* follower : npc->followers)
				{
					UE_LOG(LogTemp, Warning, TEXT("%s should be moving to the side"), *follower->GetName());
					if (!follower->movementComponent->confrontation)
					{
						follower->movementComponent->curMoveState = EMoveStates::MOVETOBATTLE;
					}

					follower->movementComponent->move = true;
				}

				for (auto* enemyFollower : enemyLeader->followers)
				{
					UE_LOG(LogTemp, Warning, TEXT("%s should be moving to the side"), *enemyFollower->GetName());
					if (!enemyFollower->movementComponent->confrontation)
					{
						enemyFollower->movementComponent->curMoveState = EMoveStates::MOVETOBATTLE;
					}

					enemyFollower->movementComponent->move = true;
				}

				npc->npcController->MoveToActor(enemyTarget);
				enemyLeader->npcController->MoveToActor(npc);
				curMoveState = EMoveStates::MOVETOENEMY;
				enemyLeader->movementComponent->curMoveState = EMoveStates::MOVETOENEMY;
			}
		}
	}

	if (npc->leader && npc->leader->movementComponent->enemyTarget != npc->leader->movementComponent->enemyLeader)
	{
		/*
		if (playerTarget)
		{
			npc->npcController->MoveToActor(playerTarget);
			curMoveState = EMoveStates::MOVETOPLAYER;
		}
		*/

		if (enemyTarget)
		{
			///UE_LOG(LogTemp, Warning, TEXT("%s is going to attack %s"), *npc->GetName(), *enemyTarget->GetName());
			npc->npcController->MoveToActor(enemyTarget);
			curMoveState = EMoveStates::MOVETOENEMY;

		} else if (followTarget && move)
		{
			///UE_LOG(LogTemp, Warning, TEXT("%s is moving to follow %s"), *npc->GetName(), *followTarget->GetName());
			npc->npcController->MoveToActor(followTarget);
			move = false;

		} else if (followTarget)
		{
			//TODO solve why those with a follow target aren't moving to side, and why leader's won't move after combat
			FVector distanceToTarget = npc->GetActorLocation() - followTarget->GetActorLocation();
			float distanceSize = FMath::Abs(distanceToTarget.Size());

			MaxWalkSpeed = (distanceSize - 500) * 0.35;
			MaxWalkSpeed = FMath::Clamp(MaxWalkSpeed, 0.0f, 600.0f);

			if (FMath::Abs(npc->movementComponent->Velocity.Size()) <= 0 && FMath::Abs(followTarget->movementComponent->Velocity.Size()) > 0 && followTarget->npcController->curState == followTarget->npcController->GetMoveState())
			{
				move = true;
			}
			///UE_LOG(LogTemp, Warning, TEXT("%s is following %s, distance is %f"), *npc->GetName(), *followTarget->GetName(), distanceSize);
		}
	} else if (npc->leader && npc->leader->movementComponent->enemyLeader && npc->leader->movementComponent->enemyTarget == npc->leader->movementComponent->enemyLeader && move)
	{
		
		//TODO if enemy follower y position is greater than leader, then move to positive 2000, else move -2000
		//Fix so that it is relative to npc's, right now they go to true y location
		//Add random to the x location as well
		int i = 0;

		if (npc->GetActorLocation().Y > npc->leader->GetActorLocation().Y)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is moving to the greater than side, follower count is %d"), *npc->GetName(), npc->leader->followers.Num());

			i = FMath::RandRange(0, 1200);
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is moving to the less than side, follower count is %d"), *npc->GetName(), npc->leader->followers.Num());

			i = FMath::RandRange(-1200, 0);
		}

		if (i > -600 && i <= 0)
		{
			i = FMath::RandRange(-1200, -600);
		}
		if (i >= 0 && i < 600)
		{
			i = FMath::RandRange(600, 1200);
		}

	
		npc->movementComponent->MaxWalkSpeed = 700;
		npc->npcController->MoveToLocation(FVector(npc->GetActorLocation().X + (i * 0.45), npc->leader->movementComponent->enemyLeader->GetActorLocation().Y + npc->leader->movementComponent->enemyLeader->GetActorForwardVector().GetSafeNormal().Y + i, npc->GetActorLocation().Z));

		move = false;
	}

}

void UNPCMovementComponent::MoveToEnemy(ANPC* npc)
{
	///UE_LOG(LogTemp, Warning, TEXT("This npc is %s is in the move to enemy state."), *npc->GetName());

	if (enemyTarget && enemyTarget->npcHealth > 0)
	{
		if (npc->isLeader)
		{
			if (enemyTarget != enemyLeader && npc->followers.Num() < (npc->followerCount / 2))
			{
				UE_LOG(LogTemp, Warning, TEXT("This npc is %s is entering move to battle state because followers are half."), *npc->GetName());

				curMoveState = EMoveStates::MOVETOBATTLE;
			}
		}

		///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, and is moving to attack %s."), *npc->GetName(), *enemyTarget->GetName());
		
		FVector distance;
		distance = npc->GetActorLocation() - enemyTarget->GetActorLocation();
		targetDistanceLength = distance.Size();
		MaxWalkSpeed = targetDistanceLength * 0.45;

		if (enemyLeader != enemyTarget)
		{
			MaxWalkSpeed = FMath::Clamp(MaxWalkSpeed, 0.0f, 650.0f);
		} else
		{
			MaxWalkSpeed = FMath::Clamp(MaxWalkSpeed, 0.0f, 250.0f);
		}

		//TODO add check if enemy target does not have player target, else movetobattle, but who to attack
		if (enemyTarget->isLeader && !enemyTarget->movementComponent->enemyTarget)
		{
			//If the enemy target is a leader and they don't have an enemy target, make this npc the target
			//UE_LOG(LogTemp, Warning, TEXT("This npc is %s, setting the enemy leader's target to me."), *npc->GetName());
			enemyTarget->movementComponent->enemyTarget = npc;
			npc->npcController->MoveToActor(enemyTarget);

		} else if (enemyTarget->isLeader && enemyTarget->movementComponent->enemyTarget && enemyTarget->movementComponent->enemyTarget == npc)
		{
			//If the enemy leader's target is this npc, check distance to attack
			if (targetDistanceLength < 190.0)
			{
				///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, attacking enemy leader target."), *npc->GetName());
				confrontation = true;

				npc->npcController->SetState(npc->npcController->GetAttackState());
				curMoveState = EMoveStates::MOVETOBATTLE;
			} else if (npc->movementComponent->Velocity.Size() < 10)
			{
				//TODO add check for if the npc isn't within distance to attack and velocity is 0
				UE_LOG(LogTemp, Warning, TEXT("%s is supposed to be moving to enemy, but is not and isn't within distance"), *npc->GetName());
			}

		} else if ( enemyTarget->isLeader && enemyTarget->movementComponent->enemyTarget && enemyTarget->movementComponent->enemyTarget != npc)
		{
			//If the enemy leader has a target and that target is not the npc, then move within a distance to the leader
			///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, leader has a different enemy target, moving to within distance."), *npc->GetName())
			if (targetDistanceLength < 1000.0 && npc->movementComponent->Velocity.X > 0)
			{
				npc->npcController->StopMovement();
			}

		}else if (!enemyTarget->isLeader && targetDistanceLength < 190.0)
		{
			//If the target is a regular enemy, then check distance then attack
			///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, attacking enemy target."), *npc->GetName());
			confrontation = true;
			

			npc->npcController->SetState(npc->npcController->GetAttackState());
			curMoveState = EMoveStates::MOVETOBATTLE;
		}
	} else if (enemyTarget && enemyTarget->movementComponent->enemyTarget != npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("The enemy: %s, has a different target than %s,"), *enemyTarget->GetName(), *npc->GetName());

	} else if (npc->playerLeader)
	{
		curMoveState = EMoveStates::FOLLOW;
	} else
	{
		curMoveState = EMoveStates::MOVETOBATTLE;
	}
}

void UNPCMovementComponent::MoveToPlayer(ANPC* npc)
{

	if (playerTarget && playerTarget->movementComponent->enemyTarget == npc)
	{
		///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, and is moving to attack %s."), *npc->GetName(), *playerTarget->GetName());

		//Here this npc will check the distance between themselves and their target until a minimum of 4 meters,
		//at which point Confrontation causes a transition to attack.

		FVector distance;
		distance = npc->GetActorLocation() - playerTarget->GetActorLocation();
		targetDistanceLength = distance.Size();


		if (targetDistanceLength <= 190.0)
		{
			UE_LOG(LogTemp, Warning, TEXT("This npc is %s, attacking enemy target."), *npc->GetName());
			confrontation = true;

			npc->stance = FMath::RandRange(0, 2);
			npc->npcController->SetState(npc->npcController->GetAttackPlayerState());
		} else
		{
			confrontation = false;
		}


		///UE_LOG(LogTemp, Warning, TEXT("This npc is %s, moving to enemy target %s and they ."), *npc->GetName(), *enemyTarget->GetName(), (enemyTarget->isLeader ? TEXT("are a leader") : TEXT("are not a leader")));
		MaxWalkSpeed = targetDistanceLength * .35;
		//TODO change moveto to call once
		npc->npcController->MoveToActor(playerTarget, 175.0);

	} else if (playerTarget)
	{
		FVector distance;
		distance = npc->GetActorLocation() - playerTarget->GetActorLocation();
		targetDistanceLength = distance.Size();

		MaxWalkSpeed = targetDistanceLength * .35;
		npc->npcController->MoveToActor(playerTarget, 500.0);

	} else
	{
		curMoveState = EMoveStates::MOVETOBATTLE;
	}
}

void UNPCMovementComponent::MoveToEvent(ANPC* npc)
{
	if (npc->GetNPCRace() == npc->GetDwarfRace() && !AWarhammerGameModeBase::dwarfEventList.Contains(npc))
	{
		AWarhammerGameModeBase::dwarfEventList.Add(npc);
		UE_LOG(LogTemp, Warning, TEXT("Adding %s to the dwarf Event List"), *npc->GetName());

	} else if (npc->GetNPCRace() == npc->GetGreenskinRace() && !AWarhammerGameModeBase::greenskinEventList.Contains(npc))
	{
		AWarhammerGameModeBase::greenskinEventList.Add(npc);
		UE_LOG(LogTemp, Warning, TEXT("Adding %s to the greenskin Event List"), *npc->GetName());
	}

	FVector distance;
	distance = npc->GetActorLocation() - npc->npcController->currentEventLocation->GetActorLocation();
	int eventDistanceLength = distance.Size();

	//UE_LOG(LogTemp, Warning, TEXT("The distance to the event position is %f."), targetDistanceLength);

	if (eventDistanceLength < 10000)
	{
		npc->npcController->SetState(npc->npcController->GetEventState());
	}
}

void UNPCMovementComponent::MoveToActivity(ANPC * npc)
{
	if (npc->activity && move)
	{
		FVector distance = npc->GetActorLocation() - npc->activity->GetActorLocation();

		if (distance.Size() > 110 && Velocity.Size() < 10)
		{
			UE_LOG(LogTemp, Warning, TEXT("not at activity and not moving"));
			npc->npcController->MoveToLocation(npc->activity->GetActorLocation(), -1.0f);
		}

		if (distance.Size() <= 110)
		{
			UE_LOG(LogTemp, Warning, TEXT("At activity"));
			
			npc->movementComponent->atActivity = true;
			npc->movementComponent->move = false;
			npc->npcController->SetState(ENPCStates::INTOWN);
		}
	}
}

void UNPCMovementComponent::Flee(ANPC* npc)
{
	//Once the npc reaches it's location, it should either move to the garrison location, or possibly move to the location specific events
	
	locationTimer++;

	if (locationTimer >= 300)
	{
		if (moveToLocation)
		{
			UE_LOG(LogTemp, Warning, TEXT("This npc is %s, is moving to their waypoint"), *npc->GetName());
			npc->npcController->MoveToActor(npc->waypoint);
			moveToLocation = false;
		}

		FVector waypointDistance = npc->GetActorLocation() - npc->waypoint->GetActorLocation();

		if (waypointDistance.Size() < 8000 && npc->waypoint != npc->previousLocation)
		{
			/*
			if the index of the previous location's array ( which is the waypoint's location in the array ) is less than the number of indices
			then increase the index, and make the value of that new index the next waypoint, then move to
			else, set the target destination to null since we are there
			*/
			UE_LOG(LogTemp, Warning, TEXT("%s is checking for next waypoint"), *npc->GetName());
			int index = npc->previousLocation->locationArrays[npc->targetDestination->location].locations.Find(npc->waypoint);

			if (index <= 0)
			{
				npc->waypoint = npc->previousLocation;
			} else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s setting next waypoint from array"), *npc->GetName());
				npc->currentLocation = npc->previousLocation->locationArrays[npc->targetDestination->location].locations[index];
				index--;
				npc->waypoint = npc->previousLocation->locationArrays[npc->targetDestination->location].locations[index];
			}

			moveToLocation = true;

		} else if (waypointDistance.Size() < 8000)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is at their flee destination"), *npc->GetName());
		}

		locationTimer = 0;

		if (npc->GetVelocity().Size() <= 0)
		{
			moveToLocation = true;
		}
	}
}

EMoveStates UNPCMovementComponent::GetNullState()
{
	return EMoveStates::NULLMOVE;
}

EMoveStates UNPCMovementComponent::GetFollowState()
{
	return EMoveStates::FOLLOW;
}

EMoveStates UNPCMovementComponent::GetMoveToBattleState()
{
	return EMoveStates::MOVETOBATTLE;
}

EMoveStates UNPCMovementComponent::GetMoveToEnemyState()
{
	return EMoveStates::MOVETOENEMY;
}

EMoveStates UNPCMovementComponent::GetMoveToPlayerState()
{
	return EMoveStates::MOVETOPLAYER;
}

EMoveStates UNPCMovementComponent::GetMoveToLocationState()
{
	return EMoveStates::MOVETOLOCATION;
}

EMoveStates UNPCMovementComponent::GetMoveToEventState()
{
	return EMoveStates::MOVETOEVENT;
}

EMoveStates UNPCMovementComponent::GetMoveToActivityState()
{
	return EMoveStates::MOVETOACTIVITY;
}

EMoveStates UNPCMovementComponent::GetFleeState()
{
	return EMoveStates::FLEE;
}

void UNPCMovementComponent::SetDefaultState(EMoveStates state)
{
	defaultState = state;
}

void UNPCMovementComponent::FilterEnemies(const TArray<AActor*> enemies, ANPC* npc)
{
	if (otherChars.Num() < 5)
	{
		for (auto* enemy : enemies)
		{
			ANPC* actor = Cast<ANPC>(enemy);

			if (ensure(actor) && actor->GetNPCRace() != npc->GetNPCRace() && !actor->isDead)
			{
				if (!otherChars.Contains(actor))
				{
					otherChars.Add(Cast<ANPC>(actor));
					hasSeenEnemy = true;
					//TODO solve issue with capsule collider colliding with self's OverlapCollider (capsule collider is set not to generate overlap events)
					///UE_LOG(LogTemp, Warning, TEXT("%s was added to %s's array"), *actor->GetName(), *npc->GetName());
				}
			}
		}
	}
}

void UNPCMovementComponent::SetPlayerTarget(APlayer_Char* player)
{
	playerTarget = player;
	curMoveState = EMoveStates::MOVETOPLAYER;
}
