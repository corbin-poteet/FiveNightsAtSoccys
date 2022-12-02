// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaggedActor.h"
#include "Camera/SecurityCamera.h"
#include "GameFramework/Actor.h"
#include "Computer.generated.h"

// dynamic multiclass delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraChangedSignature);

UCLASS()
class FIVENIGHTSATSOCCYS_API AComputer : public ATaggedActor
{
	GENERATED_BODY()

	// The mesh for the computer monitor
	UPROPERTY(Category=Computer, VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* MonitorMesh;	

public:
	AComputer();

	UPROPERTY(BlueprintAssignable)
	FOnCameraChangedSignature OnCameraChanged;

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	//~End of AActor interface

public:
	/**
	 * @brief Switches the monitor view to the camera at the given index.
	 * @param Index the index of the camera to switch to
	 */
	UFUNCTION(BlueprintCallable, Category = "Computer|Camera")
	void SwitchToCameraIndex(int32 Index);

	/**
	 * @brief Switches the monitor view to the camera at the next index.
	 */
	UFUNCTION(BlueprintCallable, Category = "Computer|Camera")
	void SwitchToNextCamera();

	/**
	 * @brief Switches the monitor view to the camera at the previous index.
	 */
	UFUNCTION(BlueprintCallable, Category = "Computer|Camera")
	void SwitchToPreviousCamera();

	UFUNCTION(BlueprintCallable, Category = "Computer|Camera")
	ASecurityCamera* GetCurrentCamera() const { return CurrentCamera; }
	
private:
	/**
	 * @brief Connects to all security cameras in the level. Called on BeginPlay.
	 * @return true if new cameras were added
	 */
	UFUNCTION(BlueprintCallable, Category = "Computer", meta = (AllowPrivateAccess = "true"))
	bool LinkToCameras();

	void LoadStreamLevelsBySoftObjectPtr();
	
	
public:
	UFUNCTION(BlueprintCallable, Category = "Computer|Info")
	FVector2D GetScreenResolution() const { return ScreenResolution; }

	UFUNCTION(BlueprintCallable, Category = "Computer|Info")
	TEnumAsByte<EPixelFormat> GetPixelFormat() const { return ScreenPixelFormat; }

private:
	UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = "true"))
	FVector2D ScreenResolution = FVector2D(240, 240);

	UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EPixelFormat> ScreenPixelFormat = EPixelFormat::PF_B8G8R8A8;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* ComputerScreenMaterialBase = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	TArray<class ASecurityCamera*> SecurityCameras;

	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	int32 CurrentCameraIndex = 0;

	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	ASecurityCamera* CurrentCamera;

	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* ScreenMaterial;

	TArray<TSoftObjectPtr<UWorld>> StreamLevelsStack;
	bool bIsStreamingLevel = false;
};
