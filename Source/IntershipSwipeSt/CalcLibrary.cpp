// Fill out your copyright notice in the Description page of Project Settings.


#include "CalcLibrary.h"

CalcLibrary::CalcLibrary()
{
}

CalcLibrary::~CalcLibrary()
{
}

double CalcLibrary::DistanceCalculation(FVector FirstPoint, FVector SecondPoint)
{
	//Vector Length Calculation
	return FMath::Sqrt((SecondPoint.X - FirstPoint.X) * (SecondPoint.X - FirstPoint.X) +
		(SecondPoint.Y - FirstPoint.Y) * (SecondPoint.Y - FirstPoint.Y));
}

FVector CalcLibrary::LineProjection(
	FVector CurrentLocation,
	FVector FirSphere,
	FVector SecSphere,
	int32& SphereID,
	int32& CurrentSphere,
	int32& CurrentLives,
	ALevelCreator*& LevelCreator,
	AInLineIndicator*& Indicator)
{
	double a, b, c, p, Height, SplineMeshDistance, Angle;

	//Finding the sides of a triangle
	a = DistanceCalculation(FirSphere, SecSphere);
	b = DistanceCalculation(CurrentLocation, FirSphere);
	c = DistanceCalculation(CurrentLocation, SecSphere);

	//Semiperimeter of a triangle
	p = (a + b + c) / 2;

	//Triangle Height
	Height = (2 * FMath::Sqrt(p * (p - a) * (p - b) * (p - c)) / a);

	SplineMeshDistance = FMath::Sqrt(b * b - Height * Height);

	Angle = ((a * a + b * b - c * c) / (2 * b * a));
	FVector DistanceFromOrigin = FVector((SecSphere.X - FirSphere.X), (SecSphere.Y - FirSphere.Y), 0);

	if (Angle < 0)
		return Indicator->GetActorLocation();


	if ((SplineMeshDistance / a) < 1) {
		FVector ShorterVector = DistanceFromOrigin * (SplineMeshDistance / a);
		FVector Final = FVector((ShorterVector.X + FirSphere.X), (ShorterVector.Y + FirSphere.Y), 50);
		if (DistanceCalculation(FirSphere, Final) <
			DistanceCalculation(FirSphere, Indicator->GetActorLocation()))
			return Indicator->GetActorLocation();
		else 
			return Final;
	}

	else {
		OnNextSphere(SphereID, CurrentSphere, CurrentLives, LevelCreator, Indicator);
		return FVector(SecSphere.X, SecSphere.Y, 50);
	}
}

bool CalcLibrary::IsSphere(AActor* HittedActor, TSubclassOf<ASphereDot> SphereClass)
{
	if (HittedActor->GetClass() == SphereClass)
		return true;
	return false;
}



void CalcLibrary::OnNextSphere(
	int32& SphereID,
	int32& CurrentSphere,
	int32& CurrentLives,
	ALevelCreator*& LevelCreator,
	AInLineIndicator*& Indicator)
{
	if (SphereID == 0) {
		if ((CurrentSphere + 1) == LevelCreator->DotsArray.Num() - 1) {
			CurrentLives++;
			LevelCreator->ClearLine();
			LevelCreator->Destroy();
			LevelCreator = nullptr;
			Indicator->Destroy();
		}
		else CurrentSphere++;
	}
	else {
		if ((CurrentSphere - 1) == 0) {
			CurrentLives++;
			LevelCreator->ClearLine();
			LevelCreator->Destroy();
			LevelCreator = nullptr;
			Indicator->Destroy();
		}
		else CurrentSphere--;
	}
}

int32 CalcLibrary::GetSphereIDFromArray(AActor* Sphere, ALevelCreator* LevelCreator)
{
	if (Sphere->GetClass() == LevelCreator->SphereDotClass) {
		for (int32 i = 0; i < LevelCreator->DotsArray.Num(); i++) {
			if (LevelCreator->DotsArray[i] == Sphere) {
				//SphereID = i;
				return i;
			}
		}
	}
	return -10;
}

int32 CalcLibrary::CalcScore(double PassedDistance, double DistanceFromLine)
{
	if (DistanceFromLine < 1)
		return PassedDistance * 10;
	else
		return PassedDistance * (FMath::Sqrt(100 / DistanceFromLine));
}

