// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/Actor.h"
#include "SecurityCamera.generated.h"

UCLASS()
class FIVENIGHTSATSOCCYS_API ASecurityCamera : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category=Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneCaptureComponent2D* SceneCaptureComponent;
	
public:
	// Sets default values for this actor's properties
	ASecurityCamera();

	
	void SetFrameRate(float NewFrameRate);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera")
	UTextureRenderTarget2D* GetCameraOutput() const { return SceneCaptureComponent->TextureTarget; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool LinkToComputer(const class AComputer* Computer);

private:

	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float FrameRate = 10.0f;

	FTimerHandle FrameTimerHandle;

	UFUNCTION()
	void UpdateCamera() const;

	//UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = "true"))
	//UTextureRenderTarget2D* TextureRenderTarget = nullptr;
};
