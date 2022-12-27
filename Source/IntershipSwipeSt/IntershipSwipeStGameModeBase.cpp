// Copyright Epic Games, Inc. All Rights Reserved.


#include "IntershipSwipeStGameModeBase.h"


void AIntershipSwipeStGameModeBase::BeginPlay()
{
}

void AIntershipSwipeStGameModeBase::CreateLevelFunc(int32 LevelNum, ULevelsData* LevelsAssets)
{
	bIsLevelCreated = true;
	//spawning level
	FTransform LevelCreatorTransform(FVector(0, 0, 0));

	FLevelSet ChosenLevel = Cast<ULevelsData>(LevelsAssets)->Levels[LevelNum - 1];
	for (FElementData& Iterator : ChosenLevel.GameElements) {
		NewLevel = GetWorld()->SpawnActor<ALevelCreator>(LevelCreator, LevelCreatorTransform);
		LevelsArray.Add(NewLevel);
		for (FVector2D& VectorIterator : Iterator.Points) {
			NewLevel->AddSphere(VectorIterator.X, VectorIterator.Y);
		}
	}
}
