// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelCreator.h"
#include "PlayerStateBase.h"
#include "Kismet/GameplayStatics.h"
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

	UPROPERTY()
	ALevelCreator* NewLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ALevelCreator> LevelCreator;

	UPROPERTY(BlueprintReadWrite)
	bool bIsLevelCreated;

protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void CreateLevelFunc(int32 LevelNum);

};
