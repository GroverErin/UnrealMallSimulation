// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MallAgentStateMachine.h"
#include "MallInteractable.generated.h"

//class ACharacter;
class GROVERGAP321FINAL_API InteractableState
	: public State
{
public:
	//----------------------------------------
	//This should probably be a Component??
	//----------------------------------------

	InteractableState(); //Does this need to be = default too??
	virtual ~InteractableState() = default;

	void Intialize(float newMotiveDecay, float motiveBoostValue);

	//Initialized the state.
	virtual void Enter(ACharacter* pOwner) final override;

	//Updates the state.
	virtual void Update(float deltaTime) final override;

	//Cleans up the state before exit.
	virtual void Exit() final override;

private:

	bool m_isFirstUpdate;
	float m_prevMotiveDecay;
	float m_newMotiveDecay;
	float m_motiveBoostValue;

};


UCLASS()
class GROVERGAP321FINAL_API AMallInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMallInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	InteractableState& GetInteractionState() { return m_state; }

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	float GetMotiveDecay() { return newMotiveDecay; }

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	float GetMotiveBoost() { return motiveBoostValue; }

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void SetMotiveDecay(float newDecay) { newMotiveDecay = newDecay; }

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void SetMotiveBoost(float newBoost) { motiveBoostValue = newBoost; }

private:
	/**The rate in at which the agents motive value will change while in this interation.*/
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float newMotiveDecay;

	/**The boost given when beginning this interation.*/
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float motiveBoostValue;

	InteractableState m_state;
};
