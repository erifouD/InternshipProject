// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"

void APlayerStateBase::AddScore(int points, int level_id)
{
	if ((PointsArray[level_id - 1]) < points)
		PointsArray[level_id - 1] = points;
}

void APlayerStateBase::ImportScore(TArray<int32> PointsArrayImport)
{
	PointsArray = PointsArrayImport;
}
