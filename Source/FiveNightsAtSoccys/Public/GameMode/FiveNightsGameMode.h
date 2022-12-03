// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "UObject/Object.h"
#include "Math/Range.h"
#include "FiveNightsGameMode.generated.h"

USTRUCT(BlueprintType)
struct FAnimatronicSettings
{
	FAnimatronicSettings()
	{
		StartingDifficulty = 0;
		ActivationTime = FDateTime(1995, 1, 1, 0, 0, 0, 0);
	}

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Difficulty", meta=(AllowPrivateAccess = "true"))
	int32 StartingDifficulty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Difficulty", meta=(AllowPrivateAccess = "true", ShowInnerProperties = "true", EditInline = "true"))
	FDateTime ActivationTime;
};



/**
 * 
 */
UCLASS()
class FIVENIGHTSATSOCCYS_API AFiveNightsGameMode : public AGameModeBase
{
public:
	AFiveNightsGameMode();
private:
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Night", meta=(AllowPrivateAccess = "true"))
	int32 NightNumber;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Night", meta=(AllowPrivateAccess = "true"))
	FDateTime StartTime = FDateTime(1995, 1, 1, 0, 0, 0);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Night", meta=(AllowPrivateAccess = "true"))
	FDateTime EndTime = FDateTime(1995, 1, 1, 6, 0, 0);

	UPROPERTY(BlueprintReadOnly, Category = "Config|Night", meta=(AllowPrivateAccess = "true"))
	FDateTime CurrentTime = FDateTime(1995, 1, 1, 0, 0, 0);
	
	UPROPERTY(BlueprintReadOnly, Category = "Config|Difficulty", meta=(AllowPrivateAccess = "true"))
	int32 MaxDifficulty = 20;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Difficulty", meta=(AllowPrivateAccess = "true", ShowOnlyInnerProperties = "true", ShowInnerProperties = "true", EditInline = "true"))
	TMap<FGameplayTag, FAnimatronicSettings> AnimatronicSettings;
	
	// The time multiplier to convert real time to game time
	// RealSeconds * TimeDilation = GameSeconds
	// 1 real second * 40.0f = 40 game seconds
	// 90 real seconds * 40.0f = 3600 game seconds = 1 game hour
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Night", meta=(AllowPrivateAccess = "true"))
	float TimeDilation = 40.f;

	FTimerHandle NightTimerHandle;

	void AddSecond();

	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = "true"))
	void Win();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta=(AllowPrivateAccess = "true"))
	void OnWin();

	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = "true"))
	void Lose();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, meta=(AllowPrivateAccess = "true"))
	void OnLose();

public:
	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	int32 GetNightNumber() const { return NightNumber; }

	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	FDateTime GetStartTime() const { return StartTime; }

	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	FDateTime GetEndTime() const { return EndTime; }

	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	FDateTime GetCurrentTime() const { return CurrentTime; }

	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	float GetTimeDilation() const{ return TimeDilation;	}

	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	void SetTimeDilation(const float NewTimeDilation){ TimeDilation = NewTimeDilation; }

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaSeconds) override;
};
