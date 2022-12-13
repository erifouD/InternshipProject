// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "SphereDot.generated.h"

UCLASS()
class INTERSHIPSWIPEST_API ASphereDot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASphereDot();


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMaterial> SphereMaterial;


	//The sphere that will be visible in the game
	UPROPERTY()
	UStaticMeshComponent* VisibleSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
