// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class INTERSHIPSWIPEST_API APlayerStateBase : public APlayerState
{
	GENERATED_BODY()

public:

	//An array that storing level points
	UPROPERTY()
	TArray<int32> PointsArray = {0, 0, 0, 0};

public:
	//Rewriting score records
	UFUNCTION()
	void AddScore(int points, int level_id);

	//Importing score from save
	UFUNCTION(BlueprintCallable)
	void ImportScore(TArray<int32> PointsArrayImport);
};
