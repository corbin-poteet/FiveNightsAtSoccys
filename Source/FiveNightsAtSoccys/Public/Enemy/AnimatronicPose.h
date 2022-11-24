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

	// The main skeletal mesh associated with this animatronic (optional sub-object).
	UPROPERTY(Category=Character, VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;

public:
	// Sets default values for this actor's properties
	AAnimatronicPose();

	//~AActor interface
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//~End of AActor interface

	/**
	 * @brief Activates and deactivates the animatronic.
	 * @param bNewActivated true if the animatronic should be activated.
	 */
	UFUNCTION(BlueprintCallable, Category = "Animatronic")
	void ActivateAnimatronic(bool bNewActivated);


private:
	// True if the animatronic is activated. If false, the animatronic will not move.
	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool bAnimatronicActivated = false;

	// True if this pose kills the player.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	bool bKillPose = false;

	// True if this is the first pose in the animatronic's sequence.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	bool bStartingPose = false;

public:
	/**
	 * @return the next animatronic pose to activate. Self if no pose is found.
	 */
	UFUNCTION(BlueprintCallable, Category = "Animatronic")
	AAnimatronicPose* SelectNextPose();

	// The animatronic tag that this pose is associated with.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	FGameplayTag AnimatronicTag;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	bool IsActivated() const { return bAnimatronicActivated; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	bool IsKillPose() const { return bKillPose; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	bool IsBlocked() const { return bBlocked; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	bool IsStartingPose() const { return bStartingPose; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Animatronic")
	USkeletalMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintCallable, Category = "Animatronic")
	void SetBlocked(bool bNewBlocked) { bBlocked = bNewBlocked; }

	UFUNCTION(BlueprintCallable, Category = "Animatronic")
	TArray<AAnimatronicPose*> GetNextPoseCandidates() const { return NextPoseCandidates; }


private:
	// The next poses that can be selected after this pose.
	UPROPERTY(EditInstanceOnly, Category = "Animatronic", meta = (AllowPrivateAccess = "true"))
	TArray<AAnimatronicPose*> NextPoseCandidates;

	// The cameras that can see this pose.
	UPROPERTY(EditInstanceOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TArray<ASecurityCamera*> WatchingCameras;

	// Whether this pose is can be activated.
	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	bool bBlocked;


#if WITH_EDITORONLY_DATA
public:
	/**
	 * @brief Called whenever an object is selected in the editor viewport.
	 * @param Object the currently selected object
	 */
	void OnSelected(UObject* Object);
private:
	/**
	 * @brief Draws debug lines to each of the next pose candidates.
	 */
	void ShowDebugLinks() const;
#endif
};
