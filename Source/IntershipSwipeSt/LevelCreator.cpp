// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelCreator.h"

// Sets default values
ALevelCreator::ALevelCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ALevelCreator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelCreator::AddSphere(float x, float y)
{
	DotsPositions.Add(FVector2D(x, y));
}

void ALevelCreator::ClearLine()
{
	for (ASphereDot*& Iterator : DotsArray) {
		Iterator->Destroy();
	}
	NewLine->Destroy();
	this->Destroy();
}

void ALevelCreator::SpawnLevel()
{
	for (FVector2D& Iterator : DotsPositions) {
		//Setting Transform for NewSphere
		FTransform SphereTransform(FVector(Iterator.X, Iterator.Y, 0));

		ASphereDot* NewSphere = GetWorld()->SpawnActor<ASphereDot>(SphereDotClass, SphereTransform);

		//creating spline if Array of spheres is empty
		if (DotsArray.Num() == 0)
			NewLine = GetWorld()->SpawnActor<ASplineLine>(SplineLineClass, SphereTransform);

		else
			NewLine->AddSplineElement(Iterator.X, Iterator.Y);

		DotsArray.Add(NewSphere);
	}

	GetWorldTimerManager().ClearTimer(ElementTimer);
	GetWorldTimerManager().SetTimer(ElementTimer, this, &ALevelCreator::ClearLine, LifeTime);

}

void ALevelCreator::StartTimer()
{
	if (SpawnTime == 0.f)
		SpawnLevel();
	else
		GetWorldTimerManager().SetTimer(ElementTimer, this, &ALevelCreator::SpawnLevel, SpawnTime);
}

bool ALevelCreator::bIsElementIsDot()
{
	if (DotsArray.Num() == 1)
		return true;
	return false;
}

