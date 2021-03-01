// Fill out your copyright notice in the Description page of Project Settings.


#include "MallAgentCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationTypes.h"
#include "NavigationSystem.h"
#include "Engine.h"
#include <algorithm>
#include "MallPlayerPawn.h"
#include "MallInteractable.h"

// Sets default values
AMallAgentCharacter::AMallAgentCharacter()
	: inertiaMultiplier(1.2f)
	, m_pCurrentMotive(nullptr)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMallAgentCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_StateMachine.InitializeStateMachine(this);
}

// Called every frame
void AMallAgentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_StateMachine.UpdateCurrentState(DeltaTime);
}

// Called to bind functionality to input
void AMallAgentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMallAgentCharacter::CalculateUtilityScores()
{
	TArray<UMotiveComponent*> motiveArray;
	GetComponents<UMotiveComponent>(motiveArray);
	for (auto pMotive : motiveArray)
	{
		pMotive->CalculateUtilityScore();
	}
}

bool AMallAgentCharacter::FindBestActionFromMotives()
{
	//Loop through all the Motive Components and Find the one with the highest utility score.
	TArray<UMotiveComponent*> motiveArray;
	GetComponents<UMotiveComponent>(motiveArray);
	UMotiveComponent* pSelectedMotive = nullptr;

	for (auto pMotive : motiveArray)
	{
		pSelectedMotive = CompareMotives(pMotive, pSelectedMotive);
	}

	//If there is a motive currently in action...
	if (m_pCurrentMotive)
	{
		//Then apply the inertia multiplier and compare.
		if (pSelectedMotive->GetUtilityScore() > (m_pCurrentMotive->GetUtilityScore() * inertiaMultiplier))
		{
			//New motive is better so change it.
			m_pCurrentMotive = pSelectedMotive;
			return true; //Best action has changed, should perform new action.
		}
	}
	else //No current action.
	{
		//Set this motive as the current "new" motive.
		m_pCurrentMotive = pSelectedMotive;
		return true; //Best action has changed, should perform new action.
	}

	return false; //Best action has NOT changed, stay in current action.
}

bool AMallAgentCharacter::PerformBestAction()
{
	//Get the tag from the current motive.
	auto tag = m_pCurrentMotive->GetMotiveTag();

	if (tag.Compare(FName(TEXT("Default"))) == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Not Correct Tag Found!: "));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, tag.GetPlainNameString());
		return false;
	}

	auto player = static_cast<AMallPlayerPawn*>(GetWorld()->GetFirstPlayerController()->GetPawn());

	auto actorList = player->GetActorList(tag);

	if (actorList.size() > 0)
	{
		SetStateFromRandomTarget(actorList);
	}
	else if (m_pCurrentMotive->GetMotiveValue() > 0.0f) //This motive has not been 'zeroed'
	{
		//Set this motive score to 0 and re-search.
		m_pCurrentMotive->ResetUtilityScore();
		FindBestActionFromMotives();
		return PerformBestAction();
	}
	else
	{
		//There is nothing with this tag so exit.
		return false;
	}

	return true;
}

void AMallAgentCharacter::SetTargetPosition(FVector newPosition)
{
	targetPosition = newPosition;
}

void AMallAgentCharacter::SetStateFromRandomTarget(const std::vector<AMallInteractable*>& actorList)
{
	int32 index = FMath::RandRange(0, actorList.size() - 1);
	if (index < actorList.size())
	{
		targetPosition = actorList[index]->GetActorLocation();

		//What is the better way to handle passing in this parameter??
		//Do these need to be const?
		m_StateMachine.QueueState(&(actorList[index]->GetInteractionState()));
	}
}

UMotiveComponent* AMallAgentCharacter::CompareMotives(UMotiveComponent* pIterMotive, UMotiveComponent* pSelectedMotive)
{ 
	//If there is an invalid interation of the motive list then bail.
	if (!pIterMotive)
		return nullptr;

	//If this is the first comparision...
	if (!pSelectedMotive)
	{
		//Set the motive and continue to the next iteration.
		pSelectedMotive = pIterMotive;
	}
	else if (pIterMotive->GetUtilityScore() > pSelectedMotive->GetUtilityScore())
	{
		//Set this motive as the current "new" motive... can still be changed on further iterations.
		pSelectedMotive = pIterMotive;
	}

	return pSelectedMotive;
}
