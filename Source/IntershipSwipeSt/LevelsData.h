// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelsData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FElementData {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector2D> Points;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double LifeTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	double SpawnTime;
};

USTRUCT(BlueprintType)
struct FLevelSet {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FElementData> GameElements;
};

UCLASS()
class INTERSHIPSWIPEST_API ULevelsData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FLevelSet> Levels;

};
