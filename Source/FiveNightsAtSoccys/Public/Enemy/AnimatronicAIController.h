// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AnimatronicPose.h"
#include "GameplayTagContainer.h"
#include "AnimatronicAIController.generated.h"


class UBehaviorTreeComponent;
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
class FIVENIGHTSATSOCCYS_API AAnimatronicAIController : public AAIController
{

private:
	GENERATED_BODY()

public:
	AAnimatronicAIController();
	
protected:
	virtual void BeginPlay() override;
	
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	FGameplayTag AnimatronicTag;

	UFUNCTION(BlueprintCallable, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	bool FindStartingPose(AAnimatronicPose*& OutStartingPose);

	UFUNCTION(BlueprintCallable, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	void SetCurrentPose(AAnimatronicPose* NewPose);
	
	UPROPERTY(BlueprintReadOnly, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	AAnimatronicPose* CurrentPose;

	UPROPERTY(BlueprintReadWrite, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	UBlackboardData* BlackboardData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animatronic|AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animatronic|AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animatronic|AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UFUNCTION(BlueprintCallable, Category = "Animatronic|AI", meta = (AllowPrivateAccess = "true"))
	void Move();
	

	
};
