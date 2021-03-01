// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MallAgentCharacter.h"
#include "GroverGAP321FinalGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GROVERGAP321FINAL_API AGroverGAP321FinalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

    AGroverGAP321FinalGameModeBase()
    {
        DefaultPawnClass = AMallAgentCharacter::StaticClass();
    }
};
