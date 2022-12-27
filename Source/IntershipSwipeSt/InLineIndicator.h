// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "InLineIndicator.generated.h"

UCLASS()
class INTERSHIPSWIPEST_API AInLineIndicator : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AInLineIndicator();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RedDot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
