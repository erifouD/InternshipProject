// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereDot.h"

// Sets default values
ASphereDot::ASphereDot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting up Default Sphere
	VisibleSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleSphere"));
	VisibleSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	VisibleSphere->SetCollisionResponseToAllChannels(ECR_Overlap);


}

// Called when the game starts or when spawned
void ASphereDot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASphereDot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

