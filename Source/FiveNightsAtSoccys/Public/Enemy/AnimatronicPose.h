// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Camera/SecurityCamera.h"
#include "GameFramework/Actor.h"
#include "AnimatronicPose.generated.h"

UCLASS()
class FIVENIGHTSATSOCCYS_API AAnimatronicPose : public AActor
{

private:
	GENERATED_BODY()

	/** The main skeletal mesh associated with this Character (optional sub-object). */
	UPROPERTY(Category=Character, VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;
	
public:
	/** Name of the MeshComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName MeshComponentName;
	
	
	void OnObjectSelected(UObject* Object);
	
	
	// Sets default values for this actor's properties
	AAnimatronicPose();

	

	
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	bool IsActivated() const { return bAnimatronicActivated; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	bool IsKillPose() const { return bKillPose; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	bool IsBlocked() const { return bBlocked;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	bool IsStartingPose() const	{ return bStartingPose; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	USkeletalMeshComponent* GetMesh() const { return Mesh; }


	UFUNCTION(BlueprintCallable, Category = "Animatronic")
	void ActivateAnimatronic(bool bNewActivated);

	UFUNCTION(BlueprintCallable, Category = "Animatronic")
	void SetBlocked(bool bNewBlocked) { bBlocked = bNewBlocked; }
	
	UFUNCTION(BlueprintCallable, Category = "Animatronic")
	TArray<AAnimatronicPose*> GetNextPoseCandidates() const { return NextPoseCandidates; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	bool bAnimatronicActivated = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	bool bKillPose = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	bool bStartingPose = false;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Animatronic")
	AAnimatronicPose* SelectNextPose();
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	FGameplayTag AnimatronicTag;

	void ShowDebugLinks(bool bShowDebug);
	
private:

	bool bShowDebugLinks = false;
	
	UPROPERTY(EditInstanceOnly, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	TArray<AAnimatronicPose*> NextPoseCandidates;

	UPROPERTY(EditInstanceOnly, Category = "Animatronic|Cameras", meta = (AllowPrivateAccess = "true"))
	TArray<ASecurityCamera*> WatchingCameras;

	UPROPERTY(BlueprintReadOnly, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	AAnimatronicPose* PreviousPose;

	UPROPERTY(BlueprintReadOnly, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	bool bBlocked;

	UPROPERTY(EditInstanceOnly, Category = "Animatronic|Debug", meta = (AllowPrivateAccess = "true"))
	bool bDebugPoseCandidates = false;

	UPROPERTY(EditInstanceOnly, Category = "Animatronic|Debug", meta = (AllowPrivateAccess = "true"))
	bool bDebugWatchingCameras = false;
	
};
