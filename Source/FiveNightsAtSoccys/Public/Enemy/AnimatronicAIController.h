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
	GENERATED_BODY()

public:
	AAnimatronicAIController();

	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

	/**
	 * @brief Move to the pose given by CurrentPose->SelectNextPose()
	 */
	UFUNCTION(BlueprintCallable, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	void Move();

protected:

	// Sets the current pose of the animatronic, activates it, and deactivates the previous one
	UFUNCTION(BlueprintCallable, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	void SetCurrentPose(AAnimatronicPose* NewPose);

private:
	/**
	 * @brief Finds the AAnimatronicPose that has bStartingPose set to true
	 * @param OutStartingPose Output AAnimatronicPose that has bStartingPose set to true
	 * @return true if a starting pose was found, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	bool FindStartingPose(AAnimatronicPose*& OutStartingPose);

private:
	// The gameplay tag of the animatronic. Used to find matching AAnimatronicPoses	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	FGameplayTag AnimatronicTag;

	// The current AAnimatronicPose that is activated for this animatronic
	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	AAnimatronicPose* CurrentPose;

	UPROPERTY(BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBlackboardData* BlackboardData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
};
