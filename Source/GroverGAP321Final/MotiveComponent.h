// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "MotiveComponent.generated.h"


UCLASS( ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent) )
class GROVERGAP321FINAL_API UMotiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMotiveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**Decay/Grow the Motive values.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void UpdateMotive();

	//TODO: ADD A RANGE HERE FOR TUNING
	/**Generate random starting motive value (For on BeginPlay).*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void SetMotiveRandomly(float minimumValue, float maximumValue);

	/**Change the current motive value by the input amount. Negative values will decrease, positive will increase. Return the new motive value. */
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	float ChangeMotiveValue(float motiveAmount);

	/**Set the current motive value to the input amount. Used on BeginPlay*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void SetMotiveValue(float newMotiveValue);

	/**Get the motive's current value.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	float GetMotiveValue();

	/**Get the motive's maximum value.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	float GetMaxMotiveValue();

	/**Set the motive decay amount to the input amount.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void SetMotiveDecay(float newMotiveChangeAmount);

	/**Get the motive decay amount.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	float GetMotiveDecay();

	/**Get the normalized version of the motive, a value between 0 and 1. Required before getting the utility score.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	float GetNormalizedMotive();

	/**Get the utility score of the motive, based on the associated curve and weight.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void CalculateUtilityScore();

	/**Get the utility score of the motive, based on the associated curve and weight.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	float GetUtilityScore();

	/**Reset the utility score of the motive to 0, used if there is no viable actions for this score.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void ResetUtilityScore();

	/**Get the tag of the motive.*/
	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	const FName& GetMotiveTag() const { return motiveTag; }

private:
	/**Does the motive grow or decay over time? This is used in the update function to compare to minimum or maximum motive values depending.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	bool doesMotiveGrow;

	/**The rate in seconds at which this motive will tick. Smaller values means faster ticking.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	float motiveTickRate;

	/**The starting Motive value. This will set the current Motive value to this value upon BeginPlay. Default = 0*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	float motiveStartingValue;

	/**The maximum Motive value. Motive cannot exceed this value.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	float motiveMaximumValue;

	/**The current Motive value. This is the value that changes throughout the simulation.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	float currentMotiveValue;

	/**The amount that the Motive value will change after each Motive Tick (set by motiveTickRate), negative means decay, positive is growth.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	float motiveChangeAmount;

	/**The multiplier that changes how the Motive will be valued over other motives when scored.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	float motiveWeight;

	/**The score that gets calculated with the utility curve and weight of this motive..*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	float motiveUtilityScore;

	/**The curve representing the real life change in this motive and it's effect psychologically on human decision making.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* motiveUtilityCurve;

	/**The tag that attributes this motive to actions in the mall.*/
	UPROPERTY(EditAnywhere, Category = "UtilityAI", meta = (AllowPrivateAccess = "true"))
	FName motiveTag;
};
