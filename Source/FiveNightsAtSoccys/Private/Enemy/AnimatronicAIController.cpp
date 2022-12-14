// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AnimatronicAIController.h"

#include "GameplayTagsManager.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/AnimatronicPose.h"
#include "Kismet/GameplayStatics.h"

AAnimatronicAIController::AAnimatronicAIController()
{
	PrimaryActorTick.bCanEverTick = false;

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	
	
}

void AAnimatronicAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if(AFiveNightsGameMode* FiveNightsGameMode = Cast<AFiveNightsGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		const FAnimatronicSettings Settings = FiveNightsGameMode->GetAnimatronicSettings(AnimatronicTag);
		ActivateAnimatronic(Settings);
	}
	
}

void AAnimatronicAIController::ActivateAnimatronic(FAnimatronicSettings Settings)
{
	DifficultyLevel = Settings.StartingDifficulty;

	AAnimatronicPose* StartingPose;
	if(!FindStartingPose(StartingPose))
	{
		UE_LOG(LogTemp, Error, TEXT("%s: No starting pose found for animatronic tag %s"), *GetName(), *AnimatronicTag.ToString());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s: Starting pose found: %s"), *GetName(), *StartingPose->GetName());
	check(StartingPose);
	
	SetCurrentPose(StartingPose);

	//TODO: Register Animatronic with AnimatronicManager

	if (IsValid(BehaviorTree))
	{
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BlackboardComponent->SetValueAsFloat("WaitTime", WaitTime);
		BlackboardComponent->SetValueAsInt("DifficultyLevel", DifficultyLevel);
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}

bool AAnimatronicAIController::FindStartingPose(AAnimatronicPose*& OutStartingPose)
{
	TArray<AActor*> AnimatronicPoses;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnimatronicPose::StaticClass(), AnimatronicPoses);
	for (AActor* Actor : AnimatronicPoses)
	{
		if (AAnimatronicPose* Pose = Cast<AAnimatronicPose>(Actor))
		{
			if (Pose->AnimatronicTag == AnimatronicTag && Pose->IsStartingPose())
			{
				OutStartingPose = Pose;
				return true;
			}
		}
	}
	
	return false;
}

void AAnimatronicAIController::SetCurrentPose(AAnimatronicPose* NewPose)
{
	if(CurrentPose)
	{
		CurrentPose->ActivateAnimatronic(false);
	}
	
	CurrentPose = NewPose;
	CurrentPose->ActivateAnimatronic(true);

}

void AAnimatronicAIController::Move()
{
	if(IsValid(CurrentPose))
	{
		SetCurrentPose(CurrentPose->SelectNextPose());
	}
}