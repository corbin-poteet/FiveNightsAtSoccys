// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"


USTRUCT()
struct FEnemySettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 DifficultyLevel = 5;
	
};



/**
 * 
 */
UCLASS()
class FIVENIGHTSATSOCCYS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
};
