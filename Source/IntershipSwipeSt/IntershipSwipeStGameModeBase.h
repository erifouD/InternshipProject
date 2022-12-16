// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelCreator.h"
#include "PlayerStateBase.h"
#include "IntershipSwipeStGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INTERSHIPSWIPEST_API AIntershipSwipeStGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	//Variable to choose Level
	UPROPERTY(BlueprintReadWrite)
	int32 LevelNumber;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALevelCreator> LevelCreator;

protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void CreateLevelFunc(int32 LevelNum);
};
