// Fill out your copyright notice in the Description page of Project Settings.


#include "MallInteractable.h"
#include "MallAgentCharacter.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationTypes.h"
#include "NavigationSystem.h"
#include "Engine.h"
#include <algorithm>
#include "MallPlayerPawn.h"

// Sets default values
AMallInteractable::AMallInteractable()
	: newMotiveDecay(0.0f)
	, motiveBoostValue(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMallInteractable::BeginPlay()
{
	Super::BeginPlay();
	m_state.Intialize(newMotiveDecay, motiveBoostValue);
}

// Called every frame
void AMallInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

InteractableState::InteractableState()
	: m_isFirstUpdate(false)
	, m_prevMotiveDecay(0.0f)
	, m_newMotiveDecay(0.0f)
	, m_motiveBoostValue(0.0f)
{
}

void InteractableState::Intialize(float newMotiveDecay, float motiveBoostValue)
{
	m_newMotiveDecay = newMotiveDecay;
	m_motiveBoostValue = motiveBoostValue;
}

void InteractableState::Enter(ACharacter* pOwner)
{
	if (!pOwner) //Don't know why this would happen but it does...
		return;

	m_pOwner = pOwner;
	m_isFirstUpdate = true;
	auto controller = m_pOwner->GetController<AAIController>();
	auto mallAgent = static_cast<AMallAgentCharacter*>(m_pOwner);
	if (controller && mallAgent)
	{
		//Get the navigation system from the world.
		UNavigationSystemV1* pNavSys = Cast<UNavigationSystemV1>(mallAgent->GetWorld()->GetNavigationSystem());
		FNavLocation resultLocation;

		//Set the target position to be a random point in a radius around the object from the above list.
		pNavSys->GetRandomPointInNavigableRadius(mallAgent->GetTargetPosition(), 200.0f, resultLocation);
		mallAgent->SetTargetPosition(resultLocation.Location);

		m_prevMotiveDecay = mallAgent->GetCurrentMotive()->GetMotiveDecay();
		controller->MoveToLocation(mallAgent->GetTargetPosition());
	}
}

void InteractableState::Update(float deltaTime)
{
	if (!m_pOwner) //Don't know why this would happen but it does...
		return;

	//If is at target.

	auto mallAgent = static_cast<AMallAgentCharacter*>(m_pOwner);
	if (m_isFirstUpdate)
	{
		//Boost the current motive of this agent.
		mallAgent->GetCurrentMotive()->ChangeMotiveValue(m_motiveBoostValue);
		m_isFirstUpdate = !m_isFirstUpdate;
	}
	//Change Motive growth/decay
	mallAgent->GetCurrentMotive()->SetMotiveDecay(m_newMotiveDecay);
}

void InteractableState::Exit()
{
	if (!m_pOwner) //Don't know why this would happen but it does...
		return;

	//Revert motive growth/decay.
	auto mallAgent = static_cast<AMallAgentCharacter*>(m_pOwner);
	mallAgent->GetCurrentMotive()->SetMotiveDecay(m_prevMotiveDecay);

	m_pOwner = nullptr;
	m_isFirstUpdate = false;

	//Pay Player.
}
