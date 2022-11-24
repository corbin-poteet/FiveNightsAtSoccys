// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UObject/Object.h"
#include "FiveNightsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FIVENIGHTSATSOCCYS_API AFiveNightsGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Night", meta=(AllowPrivateAccess = "true"))
	int32 NightNumber;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Night", meta=(AllowPrivateAccess = "true"))
	FTimespan StartTime = FTimespan( 0, 0, 0);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Night", meta=(AllowPrivateAccess = "true"))
	FTimespan EndTime = FTimespan( 6, 0, 0);

	// The time multiplier to convert real time to game time
	// RealSeconds * TimeDilation = GameSeconds
	// 1 real second * 40.0f = 40 game seconds
	// 90 real seconds * 40.0f = 3600 game seconds = 1 game hour
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config|Night", meta=(AllowPrivateAccess = "true"))
	float TimeDilation = 40.f;

public:
	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	int32 GetNightNumber() const { return NightNumber; }

	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	FTimespan GetStartDateTime() const	{ return StartTime;	}

	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	FTimespan GetEndDateTime() const{ return EndTime; }

	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	float GetTimeDilation() const{ return TimeDilation;	}

	UFUNCTION(BlueprintCallable, Category = "State", meta=(AllowPrivateAccess = "true"))
	void SetTimeDilation(const float NewTimeDilation){ TimeDilation = NewTimeDilation; }

};
