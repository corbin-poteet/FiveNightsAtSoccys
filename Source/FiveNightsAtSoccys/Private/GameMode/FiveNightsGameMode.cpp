// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FiveNightsGameMode.h"

#include "Kismet/GameplayStatics.h"

AFiveNightsGameMode::AFiveNightsGameMode()
{
	//this->CustomTimeDilation = TimeDilation;
}

FAnimatronicSettings AFiveNightsGameMode::GetAnimatronicSettings(FGameplayTag AnimatronicTag)
{
	return *AnimatronicSettings.Find(AnimatronicTag);
}

void AFiveNightsGameMode::AddSecond()
{
	const FTimespan Second = FTimespan(0, 0, 1);
	CurrentTime = CurrentTime + Second;

	if(CurrentTime >= EndTime)
	{
		Win();
	}
}

void AFiveNightsGameMode::Win()
{
	CurrentTime = EndTime;
	NightTimerHandle.Invalidate();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	OnWin();
}

void AFiveNightsGameMode::Lose()
{
	NightTimerHandle.Invalidate();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	OnLose();
}

void AFiveNightsGameMode::BeginPlay()
{
	Super::BeginPlay();

	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilation);
	CurrentTime = StartTime;

	// set timer to add a second to currenttime every second
	GetWorldTimerManager().SetTimer(NightTimerHandle, this, &AFiveNightsGameMode::AddSecond, 1.0f / TimeDilation, true);

	
	
}

void AFiveNightsGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	
	//CurrentTime = CurrentTime + DeltaSeconds;
}
