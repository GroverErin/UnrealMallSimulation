// Fill out your copyright notice in the Description page of Project Settings.


#include "MallPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine.h"
#include "MallInteractable.h"

// Sets default values
AMallPlayerPawn::AMallPlayerPawn()
	: currentMallMoney(0)
	, mallPopularity(0)
	, mallPopulation(0)
	, maxMallPopulation(0)
	, mallMaintenanceCost(0)
	, mallMaintenanceBillCycle(0.0f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//If there are actors in the world that are available with tag...
	TArray<AActor*> actorList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMallInteractable::StaticClass(), actorList);
	if (actorList.IsValidIndex(0))
	{
		for (auto& actor : actorList)
		{
			for (auto tag : actor->Tags)
			{
				auto it = m_actorMap.find(tag);
				if (it != m_actorMap.end())
				{
					it->second.emplace_back(static_cast<AMallInteractable*>(actor));
				}
				else
				{
					m_actorMap.emplace(FName{ tag }, std::vector<AMallInteractable*>{ static_cast<AMallInteractable*>(actor) });
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void AMallPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	mallPopularity = m_actorMap.size();
}

// Called every frame
void AMallPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMallPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

std::vector<AMallInteractable*>& AMallPlayerPawn::GetActorList(FName& tag)
{
	return m_actorMap[tag];
}

void AMallPlayerPawn::AddActorToMap(AMallInteractable* actor)
{
	for (auto tag : actor->Tags)
	{
		auto it = m_actorMap.find(tag);
		if (it != m_actorMap.end())
		{
			it->second.emplace_back(actor);
		}
		else
		{
			m_actorMap.emplace(FName{ tag }, std::vector<AMallInteractable*>{ actor });
		}
	}

	mallPopularity = m_actorMap.size();
}

