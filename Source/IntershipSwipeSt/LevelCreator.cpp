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

void ALevelCreator::AddSphere(int x, int y)
{
	//Setting Position for NewSphere
	FVector SpherePosition;
	SpherePosition.X = x;
	SpherePosition.Y = y;
	SpherePosition.Z = 0;

	//Setting Transform for NewSphere
	FTransform SphereTransform(SpherePosition);

	ASphereDot* NewSphere = GetWorld()->SpawnActor<ASphereDot>(SphereDotClass, SphereTransform);
	DotsArray.Add(NewSphere);
}

void ALevelCreator::Level1()
{

}

void ALevelCreator::Level2()
{

}

void ALevelCreator::Level3()
{

}

void ALevelCreator::Level4()
{

}

