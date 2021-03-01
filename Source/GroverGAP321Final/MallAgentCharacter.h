// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <vector>
#include "MotiveComponent.h"
#include "MallAgentStateMachine.h"
#include "MallAgentCharacter.generated.h"
class AMallInteractable;

UCLASS()
class GROVERGAP321FINAL_API AMallAgentCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMallAgentCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/**Goes through the list of motives and calculates the scores.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void CalculateUtilityScores();

	/**Goes through the list of motives and compares the scores. Returns if new action should be performed.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	bool FindBestActionFromMotives();

	/**Performs an action based on the current best utility scoring motive.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	bool PerformBestAction();

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void SetTargetPosition(FVector newPosition);

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	const FVector& GetTargetPosition() const { return targetPosition; }

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	UMotiveComponent* GetCurrentMotive() { return m_pCurrentMotive; }

private:

	/**The multiplier added to the current actions utility score.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	float inertiaMultiplier;

	/**The target position of the action the agent is performing.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	FVector targetPosition;

	void SetStateFromRandomTarget(const std::vector<AMallInteractable*>& actorList);

	/**Compares the utility scores of the two input motives, returns the highest scorer.*/
	UMotiveComponent* CompareMotives(UMotiveComponent* pIterMotive, UMotiveComponent* pSelect);
	
	UMotiveComponent* m_pCurrentMotive;

	MallAgentStateMachine m_StateMachine;
};
