// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Computer.generated.h"

UCLASS()
class FIVENIGHTSATSOCCYS_API AComputer : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Category=Computer, VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* MonitorMesh;
	

public:
	// Sets default values for this actor's properties
	AComputer();

	UFUNCTION(BlueprintCallable, Category = "Computer|Info")
	FVector2D GetScreenResolution() const { return ScreenResolution; }
	
	UFUNCTION(BlueprintCallable, Category = "Computer|Info")
	TEnumAsByte<EPixelFormat> GetPixelFormat() const { return ScreenPixelFormat; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Computer|Camera")
	void SwitchToCameraIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Computer|Camera")
	void SwitchToNextCamera();

	UFUNCTION(BlueprintCallable, Category = "Computer|Camera")
	void SwitchToPreviousCamera();
	
private:
	
	/**
	 * @brief Connects to all security cameras in the level
	 * @return true if new cameras were added
	 */
	UFUNCTION(BlueprintCallable, Category = "Computer", meta = (AllowPrivateAccess = "true"))
	bool LinkToCameras();
public:
	virtual void OnConstruction(const FTransform& Transform) override;
private:
	UPROPERTY(BlueprintReadOnly, Category = "Computer", meta = (AllowPrivateAccess = "true"))
	TArray<class ASecurityCamera*> SecurityCameras;
	
	UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = "true"))
	FVector2D ScreenResolution = FVector2D(240, 240);

	UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EPixelFormat> ScreenPixelFormat = EPixelFormat::PF_B8G8R8A8;

	UPROPERTY(BlueprintReadOnly, Category = "Computer", meta = (AllowPrivateAccess = "true"))
	int32 CurrentCameraIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* ComputerScreenMaterialBase = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Computer", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* ScreenMaterial;
};
