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
	ALevelCreator* LevelCreator,
	AInLineIndicator* Indicator)
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
		return FVector(FirSphere.X, FirSphere.Y, 50);

	else if ((SplineMeshDistance / a) < 1) {
		FVector ShorterVector = DistanceFromOrigin * (SplineMeshDistance / a);
		FVector Final = FVector((ShorterVector.X + FirSphere.X), (ShorterVector.Y + FirSphere.Y), 50);
		return Final;
	}

	else {
		OnNextSphere(SphereID, CurrentSphere, LevelCreator, Indicator);
		return FVector(SecSphere.X, SecSphere.Y, 50);
	}
}

bool CalcLibrary::IsSphere(AActor* HittedActor, ALevelCreator* LevelCreator)
{
	if (HittedActor->GetClass() == LevelCreator->SphereDotClass)
		return true;
	else return false;
}


void CalcLibrary::OnNextSphere(
	int32& SphereID, 
	int32& CurrentSphere, 
	ALevelCreator* LevelCreator,
	AInLineIndicator* Indicator)
{
	if (SphereID == 0) {
		if ((CurrentSphere + 1) == LevelCreator->DotsArray.Num() - 1) {
			LevelCreator->ClearLine();
			Indicator->Destroy();
		}
		else CurrentSphere++;
	}
	else {
		if ((CurrentSphere - 1) == 0) {
			LevelCreator->ClearLine();
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

