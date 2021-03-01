// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <unordered_map>
#include "MallPlayerPawn.generated.h"

struct FNameHasher
{
	std::size_t operator()(FName const& inputFName) const noexcept
	{
		std::size_t hashresult = std::hash<std::string>{}(TCHAR_TO_UTF8(*inputFName.ToString()));
		return hashresult;
	}
};

class AMallInteractable;

UCLASS()
class GROVERGAP321FINAL_API AMallPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMallPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Return the list of actors with the given tag.
	std::vector<AMallInteractable*>& GetActorList(FName& tag);

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	void AddActorToMap(AMallInteractable* actor);

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	int GetPopulation() { return mallPopulation; }

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	int GetMaxPopulation() { return maxMallPopulation; }

	UFUNCTION(BlueprintCallable, Category = UtilityAI)
	int GetMallPopularity() { return mallPopularity; }

private:

	/**The current amount of money that the mall(Player) has. This value updates throughout the game*/
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int currentMallMoney;

	/**Popularity level of the mall. This will effect how fast patrons come to the mall.*/
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int mallPopularity;

	/**The current number of patrons within the mall.*/
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int mallPopulation;

	/**The number of patrons that the mall can hold.*/
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int maxMallPopulation;

	/**The amount of money taken from the current funds each billing cycle.*/
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int mallMaintenanceCost;

	/**The rate in seconds at which the mall will get 'billed' and decrease the currentMoney.*/
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float mallMaintenanceBillCycle;

	std::unordered_map<FName, std::vector<AMallInteractable*>, FNameHasher> m_actorMap;
};
