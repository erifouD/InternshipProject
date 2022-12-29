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



	static double DistanceCalculation(FVector FirstPoint, FVector SecondPoint);

	static FVector LineProjection(
		FVector CurrentLocation, 
		FVector FirSphere, 
		FVector SecSphere,
		int32& SphereID,
		int32& CurrentSphere,
		int32& CurrentLives,
		ALevelCreator*& LevelCreator,
		AInLineIndicator*& Indicator);

	static bool IsSphere(AActor* HittedActor, ALevelCreator* LevelCreator);

	static void OnNextSphere(
		int32& SphereID,
		int32& CurrentSphere,
		int32& CurrentLives,
		ALevelCreator*& LevelCreator,
		AInLineIndicator*& Indicator);

	static int32 GetSphereIDFromArray(AActor* Sphere, ALevelCreator* LevelCreator);

	static int32 CalcScore(double PassedDistance, double DistanceFromLine);
};
