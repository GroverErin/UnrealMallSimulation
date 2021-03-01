// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//General purpose object state interface.
class GROVERGAP321FINAL_API State
{
public:
	State() {} //Does this need to be = default too??
	virtual ~State() = default;

	//Initialized the state.
	virtual void Enter(ACharacter* pOwner) {}

	//Updates the state.
	virtual void Update(float deltaTime) {}

	//Cleans up the state before exit.
	virtual void Exit() {}

protected:
	ACharacter* m_pOwner;
};

/**
 * 
 */
class GROVERGAP321FINAL_API MallAgentStateMachine
{
public:
	MallAgentStateMachine();
	~MallAgentStateMachine();

	//Initial setup required for statemachine.
	void InitializeStateMachine(ACharacter* pOwner);

	//Update the current game state.
	void UpdateCurrentState(float deltaTime);

	//Adds the given state to the queue to be added on the next update frame.
	void QueueState(State* pNewState);

private:

	//Exits the current state and enters the new state.
	void ChangeState(State* pNewState);

	//Currently active scene.
	State* m_pCurrentState;

	//Any state waiting to be loaded on the next frame.
	State* m_pNextState;

	//The initial state, does not do anything.
	State* m_pInitialState;

	//A pointer to the owner of this statemachine.
	ACharacter* m_pOwner;
};
