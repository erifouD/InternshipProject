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
	//Setting Position for NewSphere
	FVector SpherePosition;
	SpherePosition.X = x;
	SpherePosition.Y = y;
	SpherePosition.Z = 0;

	//Setting Transform for NewSphere
	FTransform SphereTransform(SpherePosition);

	ASphereDot* NewSphere = GetWorld()->SpawnActor<ASphereDot>(SphereDotClass, SphereTransform);

	//creating spline if Array of spheres is empty
	if (DotsArray.Num() == 0)
		NewLine = GetWorld()->SpawnActor<ASplineLine>(SplineLineClass, SphereTransform);

	else
		NewLine->AddSplineElement(x, y);


	DotsArray.Add(NewSphere);
}

void ALevelCreator::Level1()
{
	AddSphere(10, 12);
	AddSphere(100, -120);
	AddSphere(340, -620);
}

void ALevelCreator::Level2()
{
	AddSphere(100, -100);
	AddSphere(80, 111);
	AddSphere(450, 410);
	AddSphere(-114, 115);
	AddSphere(137, 228);
}

void ALevelCreator::Level3()
{
	AddSphere(390, 790);
	AddSphere(-450, 510);
	AddSphere(-110, 150);
	AddSphere(360, 20);
	AddSphere(90, -600);
}

void ALevelCreator::Level4()
{
	AddSphere(-500, 1220);
	AddSphere(-310, 910);
	AddSphere(530, 810);
	AddSphere(540, 290);
	AddSphere(100, 50);
	AddSphere(390, 790);
	AddSphere(320, -350);
	AddSphere(-100, 850);
}

