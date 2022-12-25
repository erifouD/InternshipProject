// Copyright Epic Games, Inc. All Rights Reserved.


#include "IntershipSwipeStGameModeBase.h"


void AIntershipSwipeStGameModeBase::BeginPlay()
{
}

void AIntershipSwipeStGameModeBase::CreateLevelFunc(int32 LevelNum)
{
	bIsLevelCreated = true;
	//spawning level
	FTransform LevelCreatorTransform(FVector(0, 0, 0));

	ALevelCreator* NewLevel = GetWorld()->SpawnActor<ALevelCreator>(LevelCreator, LevelCreatorTransform);
	switch (LevelNumber) {
	case 1: NewLevel->Level1(); break;
	case 2: NewLevel->Level2(); break;
	case 3: NewLevel->Level3(); break;
	case 4: NewLevel->Level4(); break;
	}
}
