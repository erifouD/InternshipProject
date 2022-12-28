// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelCreator.h"
#include "InLineIndicator.h"

/**
 * 
 */
class INTERSHIPSWIPEST_API CalcLibrary
{
public:
	CalcLibrary();
	~CalcLibrary();



	double DistanceCalculation(FVector FirstPoint, FVector SecondPoint);

	FVector LineProjection(
		FVector CurrentLocation, 
		FVector FirSphere, 
		FVector SecSphere,
		int32& SphereID,
		int32& CurrentSphere,
		ALevelCreator* LevelCreator,
		AInLineIndicator* Indicator);

	bool IsSphere(AActor* HittedActor, ALevelCreator* LevelCreator);

	void OnNextSphere(
		int32& SphereID,
		int32& CurrentSphere,
		ALevelCreator* LevelCreator,
		AInLineIndicator* Indicator);
};
