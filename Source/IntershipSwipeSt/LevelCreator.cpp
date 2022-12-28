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

	//Setting Transform for NewSphere
	FTransform SphereTransform(FVector(x,y,0));

	ASphereDot* NewSphere = GetWorld()->SpawnActor<ASphereDot>(SphereDotClass, SphereTransform);

	//creating spline if Array of spheres is empty
	if (DotsArray.Num() == 0)
		NewLine = GetWorld()->SpawnActor<ASplineLine>(SplineLineClass, SphereTransform);

	else
		NewLine->AddSplineElement(x, y);

	DotsArray.Add(NewSphere);
}

void ALevelCreator::ClearLine()
{
	for (ASphereDot*& Iterator : DotsArray) {
		Iterator->Destroy();
	}
	NewLine->Destroy();
}

