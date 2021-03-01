// Fill out your copyright notice in the Description page of Project Settings.


#include "MotiveComponent.h"

// Sets default values for this component's properties
UMotiveComponent::UMotiveComponent()
	: doesMotiveGrow(false)
	, motiveTickRate(2.5f)
	, motiveStartingValue(0.0f)
	, motiveMaximumValue(100.0f)
	, currentMotiveValue(0.0f)
	, motiveChangeAmount(-1.0f)
	, motiveWeight(1.0f)
	, motiveUtilityScore(0.0f)
	, motiveUtilityCurve(nullptr)
	, motiveTag(TEXT("Default"))
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = motiveTickRate;
	// ...

	currentMotiveValue = motiveStartingValue;
}


// Called when the game starts
void UMotiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMotiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	UpdateMotive();
}

void UMotiveComponent::UpdateMotive()
{
	if (!doesMotiveGrow)
	{
		float newMotiveValue = currentMotiveValue + motiveChangeAmount;
		if (newMotiveValue >= 0.0f)
			currentMotiveValue = newMotiveValue;
		else
			currentMotiveValue = 0.0f;
	}
	else
	{
		float newMotiveValue = currentMotiveValue + motiveChangeAmount;
		if (newMotiveValue <= motiveMaximumValue)
			currentMotiveValue = newMotiveValue;
		else
			currentMotiveValue = motiveMaximumValue;
	}
}

void UMotiveComponent::SetMotiveRandomly(float minimumVal, float maximumValue)
{
	currentMotiveValue = FMath::RandRange(minimumVal, maximumValue);
}

float UMotiveComponent::ChangeMotiveValue(float motiveAmount)
{
	float newMotiveValue = currentMotiveValue + motiveAmount;
	if (newMotiveValue <= motiveMaximumValue && newMotiveValue >= 0.0f)
		currentMotiveValue = newMotiveValue;
	else if (newMotiveValue > motiveMaximumValue)
		currentMotiveValue = motiveMaximumValue;
	else
		currentMotiveValue = 0.0f;

	return currentMotiveValue;
}

void UMotiveComponent::SetMotiveValue(float newMotiveValue)
{
	if (newMotiveValue <= motiveMaximumValue && newMotiveValue >= 0.0f)
		currentMotiveValue = newMotiveValue;
	else if (newMotiveValue > motiveMaximumValue)
		currentMotiveValue = motiveMaximumValue;
	else
		currentMotiveValue = 0.0f;
}

float UMotiveComponent::GetMotiveValue()
{
	return currentMotiveValue;
}

float UMotiveComponent::GetMaxMotiveValue()
{
	return motiveMaximumValue;
}

void UMotiveComponent::SetMotiveDecay(float newMotiveChangeAmount)
{
	motiveChangeAmount = newMotiveChangeAmount;
}

float UMotiveComponent::GetMotiveDecay()
{
	return motiveChangeAmount;
}

float UMotiveComponent::GetNormalizedMotive()
{
	return currentMotiveValue / motiveMaximumValue;
}

void UMotiveComponent::CalculateUtilityScore()
{
	if (motiveUtilityCurve)
	{
		motiveUtilityScore = motiveUtilityCurve->GetFloatValue(currentMotiveValue / motiveMaximumValue) * motiveWeight;
	}
	else
	{
		motiveUtilityScore = 0.0f;
	}
}

float UMotiveComponent::GetUtilityScore()
{
	return motiveUtilityScore;
}

void UMotiveComponent::ResetUtilityScore()
{
	motiveUtilityScore = 0.0f;
}