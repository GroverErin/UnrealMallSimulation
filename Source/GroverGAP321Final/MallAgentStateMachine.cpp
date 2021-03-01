// Fill out your copyright notice in the Description page of Project Settings.


#include "MallAgentStateMachine.h"

MallAgentStateMachine::MallAgentStateMachine()
	: m_pCurrentState(nullptr)
	, m_pNextState(nullptr)
	, m_pInitialState(nullptr)
{
}

MallAgentStateMachine::~MallAgentStateMachine()
{
	//Exit the current state.
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}

	//Delete the current state.
	//delete m_pCurrentState;
	m_pCurrentState = nullptr;
	
	delete m_pInitialState;
	m_pInitialState = nullptr;
}

void MallAgentStateMachine::InitializeStateMachine(ACharacter* pOwner)
{
	m_pOwner = pOwner;
	m_pInitialState = new State();
	QueueState(m_pInitialState); //Queues and empty state.
}

void MallAgentStateMachine::UpdateCurrentState(float deltaTime)
{
	//If the next state exists...
	if (m_pNextState != nullptr)
	{
		//Change to that state.
		ChangeState(m_pNextState);

		//Clear the next state.
		m_pNextState = nullptr;
	}

	//If the current state exists...
	if (m_pCurrentState != nullptr)
	{
		//Update it.
		m_pCurrentState->Update(deltaTime);
	}
}

void MallAgentStateMachine::QueueState(State* pNewState)
{
	//Prevents multi-queue.
	//delete m_pNextState;

	m_pNextState = pNewState;
}

void MallAgentStateMachine::ChangeState(State* pNewState)
{
	//Exit the current state.
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Exit();
	}

	//Delete the old state.
	//delete m_pCurrentState;

	//Load the new state.
	m_pCurrentState = pNewState;

	//Enter the new state.
	pNewState->Enter(m_pOwner);
}
